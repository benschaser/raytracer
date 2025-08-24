#include "parser.h"
#include <sstream>
#include <algorithm>
#include <stdexcept>

Parser::Parser(const std::string& filename)
    :input_filename{filename}, found_camera{false}, found_pixels{false}, found_output{false}, found_rays{false} {
    std::ifstream input{filename};
    if (!input) {
        throw std::runtime_error("Could not open " + filename);
    }
    parse(input);
    verify();
}

Camera Parser::get_camera() {
    return Camera{camera_position, camera_target, camera_up, camera_fov, aspect};
}

World Parser::get_world() {
    return world;
}

Pixels Parser::get_pixels() {
    return Pixels{columns, rows};
}

std::string Parser::get_output_filename() {
    return output_filename;
}

void Parser::parse(std::ifstream& input) {
    std::string line;
    while (std::getline(input, line)) {
        remove_comment(line);
        if (is_whitespace(line)) {
            continue;
        }

        std::stringstream ss{line};
        std::string type;
        ss >> type;
        if (type == "camera") {
            parse_camera(ss);
        }
        else if (type == "pixels") {
            parse_pixels(ss);
        }
        else if (type == "sphere") {
            parse_sphere(ss);
        }
        else if (type == "triangle") {
            parse_triangle(ss);
        }
        else if (type == "output") {
            parse_output(ss);
        }
        else if (type == "rays") {
            parse_rays(ss);
        }
        else if (type == "material") {
            parse_material(ss);
        }
        else if (type == "threads") {
            parse_threads(ss);
        }
        else if (type == "mesh") {
            parse_mesh(ss);
        }
        else {
            std::string msg{"Unrecognized type in line: " + line};
            throw std::runtime_error(msg);
        }
    }
}

void Parser::verify() {
    if (!found_camera) {
        throw std::runtime_error(input_filename + " is missing camera");
    }
    if (!found_pixels) {
        throw std::runtime_error(input_filename + " is missing pixels");
    }
    if (!found_threads) {
        throw std::runtime_error(input_filename + " is missing threads");
    }
    if (output_filename.empty()) {
        throw std::runtime_error(input_filename + " is missing output");
    }
    if (world.objects.empty()) {
        throw std::runtime_error(input_filename + " is a void");
    }
    if (!found_rays) {
        throw std::runtime_error(input_filename + " is missing rays");
    }
}

void Parser::parse_camera(std::stringstream& ss) {
    if (ss >> camera_position >> camera_target >> camera_up >> camera_fov) {
        found_camera = true;
    }
    else {
        throw std::runtime_error(input_filename + " has malformed camera");
    }
}

void Parser::parse_pixels(std::stringstream& ss) {
    if (ss >> columns >> rows) {
        found_pixels = true;
        aspect = static_cast<double>(columns) / rows;
    }
    else {
        throw std::runtime_error(input_filename + " has malformed pixels");
    }
}

void Parser::parse_sphere(std::stringstream& ss) {
    Vector3D center;
    double radius;
    std::string material_name;
    ss >> center >> radius >> material_name;
    auto i = materials.find(material_name);
    if (i != materials.end()) {
        auto material = i->second;
        world.add(std::make_shared<Sphere>(center, radius, material));
    }
    else {
        throw std::runtime_error("Unknown material: " + material_name);
    }
}
void Parser::parse_triangle(std::stringstream& ss) {
    Vector3D v0, v1, v2;
    std::string material_name;
    ss >> v0 >> v1 >> v2 >> material_name;
    auto i = materials.find(material_name);
    if (i != materials.end()) {
        auto material = i->second;
        world.add(std::make_shared<Triangle>(v0, v1, v2, material));
    }
    else {
        throw std::runtime_error("Unknown material: " + material_name);
    }
}
void Parser::parse_output(std::stringstream& ss) {
    if (ss >> output_filename) {
        found_output = true;
    }
    else {
        throw std::runtime_error(input_filename + " has malformed output");
    }
}

void Parser::parse_rays(std::stringstream& ss) {
    if (ss >> depth >> samples) {
        found_rays = true;
    }
    else {
        throw std::runtime_error(input_filename + " has malformed rays");
    }
}
void Parser::parse_material(std::stringstream& ss) {
    std::string name, kind, texture_name;
    Color color;
    bool emitting;

    ss >> name >> kind >> texture_name >> color >> std::boolalpha >> emitting;

    if (texture_name == "solid" && textures.count("solid") <= 0) {
        textures[name] = std::make_shared<Solid>(color);
    }
    else if (texture_name == "checkerboard" && textures.count("checkerboard") <= 0) {
        textures[name] = std::make_shared<Checkerboard>(color);
    }
    else if (texture_name == "gradient" && textures.count("gradient") <= 0) {
        textures[name] = std::make_shared<Gradient>(color);
    }
    else if (texture_name == "v-stripe" && textures.count("v-stripe") <= 0) {
        textures[name] = std::make_shared<VStripe>(color);
    }
    else if (texture_name == "h-stripe" && textures.count("h-stripe") <= 0) {
        textures[name] = std::make_shared<HStripe>(color);
    }
    else if (texture_name == "spiral" && textures.count("spiral") <= 0) {
        textures[name] = std::make_shared<Spiral>(color);
    }
    else {
        throw std::runtime_error("Unknown texture name: " + texture_name);
    }

    // std::shared_ptr<Texture> texture = textures[name];
    // Texture* t = texture.get();

    if (kind == "diffuse") {
        materials[name] = std::make_shared<Diffuse>(textures[name].get(), emitting);
    }
    else if (kind == "specular") {
        materials[name] = std::make_shared<Specular>(textures[name].get(), emitting);
    }
    else if (kind == "metal") {
        double fuzz;
        if (ss >> fuzz) {
            materials[name] = std::make_shared<Metal>(textures[name].get(), emitting, fuzz);
        }
        else {
            throw std::runtime_error("Missing fuzz parameter for metal");
        }
    }
    else if (kind == "glass") {
        // double n1;
        // double n2;
        // if (ss >> n1 >> n2) {
            materials[name] = std::make_shared<Glass>(textures[name].get(), emitting);
        // }
    }
    else {
        throw std::runtime_error("Unknown material: " + name);
    }

}
void Parser::parse_threads(std::stringstream& ss) {
    if (ss >> thread_count) {
        found_threads = true;
    }
    else {
        throw std::runtime_error(input_filename + " has malformed threads");
    }
}

void Parser::parse_mesh(std::stringstream& ss) {
    Vector3D position;
    std::string filename, material_name;
    if (!(ss >> position >> filename >> material_name)) {
        throw std::runtime_error("Malformed mesh line");
    }
    if (filename.substr(filename.rfind(".") + 1) == "obj") {
        parse_obj(filename, position, material_name);
        return;
    }
    // Material* material = materials[material_name].get();
    std::ifstream input{"../" + filename};
    if (!input) {
        throw std::runtime_error("Cannot open mesh file: " + filename);
    }
    std::string temp;
    input >> temp;
    if (temp != "vertices") {
        throw std::runtime_error("Mesh file must start with string 'vertices'");
    }
    std::vector<Vector3D> vertices;
    for (Vector3D vertex; input >> vertex;) {
        vertices.push_back(vertex + position);
    }
    if (vertices.size() < 3) {
        throw std::runtime_error("Mesh file must contain at least 3 vertices");
    }
    input.clear(); // clear error bit because "triangles" was read
    input >> temp; // read "triangles"
    // read each triangle line
    for (int a, b, c; input >> a >> b >> c;) {
        world.add(std::make_shared<Triangle>(vertices.at(a), vertices.at(b), vertices.at(c), materials[material_name]));
    }
}
void Parser::parse_obj(std::string filename, Vector3D position, std::string material_name) {
    std::ifstream input{"../" + filename};
    if (!input) {
        throw std::runtime_error("cannot find obj file");
    }
    std::string line, type;
    std::vector<Vector3D> vertices;
    while (std::getline(input, line)) {
        std::stringstream ss{line};
        std::string type;
        ss >> type;
        if (type == "v") {
            double x, y, z, w;
            ss >> x >> y >> z >> w;
            Vector3D vert = {x, y, z};
            vertices.push_back(vert + position);
        }
        else if (type == "f") {
            std::string init;
            int v0, v1, v2;
            ss >> init;
            int count = 0;
            for (int i = 0; i < init.size(); ++i) {
                if (init[i] == '/') count++;
            }
            if(count == 0) { // regular face definition
                v0 = std::stoi(init);
                ss >> v1 >> v2;
                if (v0 < 1) {
                    v0 = vertices.size() + v0;
                }
                if (v1 < 1) {
                    v1 = vertices.size() + v1;
                }
                if (v2 < 1) {
                    v2 = vertices.size() + v2;
                }
                world.add(std::make_shared<Triangle>(vertices.at(v0-1), vertices.at(v1-1), vertices.at(v2-1), materials[material_name]));
            }
            else if(count == 2) { // face def by normals
                std::vector<int> verts;
                std::string str_v0 = init.substr(0, init.find('/'));
                verts.push_back(std::stoi(str_v0));
                while (ss >> init) {
                    std::string str_v = init.substr(0, init.find('/'));
                    verts.push_back(std::stoi(str_v));
                }
                if (verts.size() == 3) { // triangle
                    world.add(std::make_shared<Triangle>(vertices.at(verts.at(0)-1), vertices.at(verts.at(1)-1), vertices.at(verts.at(2)-1), materials[material_name]));
                }
                else if (verts.size() == 4) {
                    std::cout << "adding tri1 " << verts.at(0) << ' ' << verts.at(1) << ' ' << verts.at(2) << '\n';
                    world.add(std::make_shared<Triangle>(vertices.at(verts.at(0)-1), vertices.at(verts.at(1)-1), vertices.at(verts.at(2)-1), materials[material_name]));
                    std::cout << "adding tri2 " << verts.at(0) << ' ' << verts.at(3) << ' ' << verts.at(2) << '\n';
                    world.add(std::make_shared<Triangle>(vertices.at(verts.at(0)-1), vertices.at(verts.at(3)-1), vertices.at(verts.at(2)-1), materials[material_name]));
                }
            }
        }
        // else {
        //     throw std::runtime_error("obj parse error");
        // }
    }

}
// std::istream& operator>>(std::istream& is, int& v0, int& v1, int& v2) {
//   char slash;
//   return is >> v0 >> slash >> v1 >> slash >> v2;
// }

void remove_comment(std::string& line) {
    auto i = line.find('#');
    if (i != std::string::npos) {
        line = line.substr(0, i);
    }
}

bool is_whitespace(const std::string& line) {
    return std::all_of(std::begin(line), std::end(line), ::isspace);
}
