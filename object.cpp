#include "object.h"
#include "constants.h"
#include "hitbox.h"


Object::Object(std::shared_ptr<Material> material, std::string type)
    :material{material}, type{type} {}


Sphere::Sphere(const Point3D& center, double radius, std::shared_ptr<Material> material)
    :center{center}, radius{radius}, Object{material, "sphere"} {
        if (radius <= 0) {
            throw std::runtime_error("Radius must be positive: " + std::to_string(radius));
        }
    }
std::optional<double> Sphere::intersect(const Ray& ray) const {
    Vector3D OC = center - ray.origin;
    double R = dot(ray.direction, OC);
    double h2 = radius*radius - dot(OC, OC) + R*R;
    if (h2 < 0) { //no hit
        return {};
    }
    double h = std::sqrt(h2);
    if ((R-h) > Constants::Epsilon) { //intersection from outside so t = R-h is closer
        return R - h;
    }
    else if ((R+h) > Constants::Epsilon) { //intersection from inside so t = R+h
        return R + h;
    }
    else { return {}; }
}
Hit Sphere::construct_hit(const Ray& ray, double time) const {
    //error handling
    Point3D point = ray.at(time);
    //error handling, possible ray.at(time) is not on sphere

    //Schaser method of calculating normals on spheres
    Vector3D normal = (point - center) / radius;
    return Hit{time, point, normal, this};
}
UV Sphere::uv(const Hit& hit) const {
    double theta = std::acos(hit.normal.z);
    double phi = std::atan2(hit.normal.y, hit.normal.x);

    double u = 0.5 + phi/(2*Constants::Pi); //[0, 1]
    double v = theta / Constants::Pi; //[0, 1]
    return {u, v};
}

Triangle::Triangle(const Point3D vertex0, const Point3D vertex1, const Point3D vertex2, std::shared_ptr<Material> material)
    :vertex0{vertex0}, vertex1{vertex1}, vertex2{vertex2}, edge1{vertex1-vertex0}, edge2{vertex2-vertex0}, Object{material, "triangle"} {
        double d = dot(edge1, edge2);
        if (d < Constants::Epsilon) {
            throw std::runtime_error("Triangle points form a line");
        }
        else {
            normal = unit(cross(edge1, edge2));
        }
    }

std::optional<double> Triangle::intersect(const Ray& ray) const {
    // Moeller-Trumbore Intersection
    Vector3D h = cross(ray.direction, edge2);
    double a = dot(edge1, h);
    if (a > -Constants::Epsilon && a < Constants::Epsilon) {
        return {}; //too close or parallel
    }

    double f = 1.0 / a;
    Vector3D s = ray.origin - vertex0;
    double u = f * dot(s, h);
    if (u <= 0 || u > 1.0) {
        return {}; //ray is outside of u: [0, 1]
    }

    Vector3D q = cross(s, edge1);
    double v = f * dot(ray.direction, q);
    if (v < 0.0 || u + v > 1.0) {
        return {};
    }

    double t = f * dot(edge2, q);
    if (t > Constants::Epsilon) {
        return t;
    }
    else {
        return {}; //no hit
    }
}
Hit Triangle::construct_hit(const Ray& ray, double time) const {
    Point3D position = ray.at(time);
    bool negative = std::signbit(dot(ray.direction, normal));
    if (negative) {
        return Hit{time, position, normal, this};
    }
    else {
        return Hit{time, position, -normal, this};
    }
}
UV Triangle::uv(const Hit& hit) const {

}

Hitbox Sphere::create_hitbox() const {
    double pad = 0.1;
    Point3D p1 = {center.x - radius - pad, center.y - radius - pad, center.z - radius - pad};
    Point3D p2 = {center.x + radius + pad, center.y + radius + pad, center.z + radius + pad};
    return Hitbox{p1, p2};
}
Hitbox Triangle::create_hitbox() const {
    double pad = 0.1;
    Point3D p1 = {min(min(vertex0.x, vertex1.x), vertex2.x) - pad, min(min(vertex0.y, vertex1.y), vertex2.y) - pad, min(min(vertex0.z, vertex1.z), vertex2.z) - pad};
    Point3D p2 = {max(max(vertex0.x, vertex1.x), vertex2.x) + pad, max(max(vertex0.y, vertex1.y), vertex2.y) + pad, max(max(vertex0.z, vertex1.z), vertex2.z) + pad};
    return Hitbox{p1, p2};
}