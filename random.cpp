#include "random.h"
#include "Xoshiro.hpp"
#include <random>

double random_double() {
    // static std::random_device rd;
    // static std::mt19937 engine{rd()};
    // static std::uniform_real_distribution<double> distribution{0.0, 1.0};
    // return distribution(engine);
    const std::uint64_t seed = 19476027648;
    static XoshiroCpp::Xoshiro256PlusPlus rng(seed);
    return XoshiroCpp::DoubleFromBits(rng());
}
double random_double(double min, double max) {
    return min + (max-min) * random_double();
}
Vector3D random_unit_vector() {
    Vector3D r{10, 10, 10};
    while (std::pow(length(r), 2) > 1) {
        r = {random_double(-1, 1), random_double(-1, 1), random_double(-1, 1)};
    }
    return unit(r);
}
Vector3D random_hemisphere(const Vector3D& normal) {
    Vector3D r = random_unit_vector();
    if (dot(r, normal) > 0.0) {
        return r;
    }
    else {
        return -r;
    }
}