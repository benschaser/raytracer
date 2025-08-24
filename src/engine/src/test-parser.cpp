#include "camera.h"
#include "color.h"
#include "constants.h"
#include "hit.h"
#include "parser.h"
#include "pixels.h"
#include "ray.h"
#include "sphere.h"
#include "world.h"
#include "random.h"

Color trace(const World& world, const Ray& ray);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " filename\n";
        return 0;
    }
    try {
        Parser parser(argv[1]);
        World world = parser.get_world();
        Pixels pixels = parser.get_pixels();
        Camera camera = parser.get_camera();
        int samples = 100;

        for (auto i = 0; i < pixels.rows; ++i) {
            std::cout << "\rProgress: " << i * 100 / pixels.rows + 1 << "%"
                      << std::flush;
            for (auto j = 0; j < pixels.columns; ++j) {
                Color color{0, 0, 0};
                for (auto sample = 0; sample < samples; ++sample) {
                    double x = (j + random_double()) / (pixels.columns - 1);
                    double y = (i + random_double()) / (pixels.rows - 1);

                    Ray ray = camera.compute_ray(x, y);
                    color += trace(world, ray);
                }
                pixels(i, j) = color / samples;
            }
        }
        std::string filename = parser.get_output_filename();
        pixels.save_png(filename);
        std::cout << "\nWrote " << filename << '\n';
    } catch (std::exception& e) {
        std::cout << e.what() << '\n';
    }
}

Color trace(const World& world, const Ray& ray) {
    std::optional<Hit> hit = world.find_nearest(ray);
    if (hit.has_value()) {
        return hit->normal;
    } else {
        return Black;
    }
}
