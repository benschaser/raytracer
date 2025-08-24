#include "engine.h"
#include <iomanip>
#include <thread>

void print_progress(long long ray_num, long long total_rays);
Color trace_path(const World& world, const Ray& ray, int depth);
void trace(Pixels& result, Pixels pixels, World world, Camera camera, int depth, int samples);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: prog filename\n";
        return 0;
    }
    try {
        Parser parser(argv[1]);
        // Parser parser("../final.txt");
        World world = parser.get_world();
        world.construct_BVH_tree();
        Pixels pixels = parser.get_pixels();
        Camera camera = parser.get_camera();
        int depth = parser.depth;
        int samples = parser.samples;
        int N = parser.thread_count;
        std::vector<std::thread> threads;
        std::vector<Pixels> results(N);
        for (int i = 1; i < N; ++i) {
            std::thread t{trace, std::ref(results.at(i)), pixels, world, camera, depth, samples/N};
            threads.push_back(std::move(t));
        }

        const long long rays_total = pixels.rows * pixels.columns * static_cast<long long>(samples);
        long long ray_num = 0;
        print_progress(ray_num, rays_total);
        for (auto i = 0; i < pixels.rows; ++i) {
            for (auto j = 0; j < pixels.columns; ++j) {
                Color color{0, 0, 0};
                for (int s = 0; s < samples/N; ++s) {
                    double x = (j + random_double()) / (pixels.columns - 1);
                    double y = (i + random_double()) / (pixels.rows - 1);
                    Ray ray = camera.compute_ray(x, y);
                    color += trace_path(world, ray, depth);
                    ray_num += N;
                    // ++ray_num;
                    if (ray_num % (rays_total / 100) == 0) {
                        print_progress(ray_num, rays_total);
                    }
                }
                pixels(i, j) = color / (samples/N);
            }
        }


        std::cout << '\r';
        auto width = std::to_string(rays_total).length() + 4;
        std::cout << std::setw(3) << "100% |";
        for (int i = 0; i < 20; ++i) {
            std::cout << "\u2588";
        }
        std::cout << '|';
        std::cout << std::setw(width) << rays_total << '/' << rays_total << " rays";
        std::cout << std::flush;


        results.at(0) = pixels;
        for (unsigned long i = 0; i < pixels.values.size(); ++i) {
            pixels.values.at(i) = Black;
        }
        for (auto& thread : threads) {
            thread.join();
        }
        for (auto r : results) {
            // std::cout << '\n' << r.values.at(500);
            for (unsigned long i = 0; i < pixels.values.size(); ++i) {
                pixels.values.at(i) += r.values.at(i);
            }
        }
        for (unsigned long i = 0; i < pixels.values.size(); ++i) {
            pixels.values.at(i) /= N;
        }
        std::string filename = parser.get_output_filename();
        pixels.save_png(filename);
        std::cout << "\nWrote " << filename << '\n';
    }
    catch (std::exception& err) {
        std::cout << err.what() << '\n';
    }
}

void print_progress(long long ray_num, long long total_rays) {
    auto width = std::to_string(total_rays).length() + 4;
    std::cout.imbue(std::locale(""));
    int percentage = std::round(static_cast<double>(ray_num) / total_rays * 100);
    std::cout << '\r';
    std::cout << std::setw(3) << percentage << "% |";
    for (int i = 0; i < percentage/5; ++i) {
        std::cout << "\u2588";
    }
    for (int i = 0; i < (20-percentage/5); ++i) {
        std::cout << "\u2581";
    }
    std::cout << '|';
    
    std::cout << std::setw(width) << ray_num << '/' << total_rays << " rays";
    std::cout << std::flush;
}

Color trace_path(const World& world, const Ray& ray, int depth) {
    if (depth == 0) {
        return Black;
    }
    std::optional<Hit> hit = world.find_nearest_BV(ray);
    if (!hit.has_value()) {
        return Black;
    }
    UV uv = hit->object->uv(hit.value());
    Material* material = hit->object->material.get();
    Texture* texture = material->texture;
    
    Color color = texture->uv(uv.first, uv.second);
    if (material->emitting) {
        return color * std::pow(std::abs(dot(hit->normal, ray.direction)), 0.33);
    }
    Ray scattered = material->scatter(ray, hit.value());
    return trace_path(world, scattered, depth-1) * color;
}
void trace(Pixels& result, Pixels pixels, World world, Camera camera, int depth, int samples) {
    for (auto i = 0; i < pixels.rows; ++i) {
        for (auto j = 0; j < pixels.columns; ++j) {
            Color color{0, 0, 0};
            for (int s = 0; s < samples; ++s) {
                double x = (j + random_double()) / (pixels.columns - 1);
                double y = (i + random_double()) / (pixels.rows - 1);
                Ray ray = camera.compute_ray(x, y);
                color += trace_path(world, ray, depth);
            }
            pixels(i, j) = color / samples;
        }
    }
    result = pixels;
}
