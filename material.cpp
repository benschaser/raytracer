#include "material.h"
#include <cmath>
#include "ray.h"
#include "hit.h"
#include "random.h"
#include "constants.h"

Material::Material(std::string name, Texture* texture, bool emitting)
    :name{name}, texture{texture}, emitting{emitting} {}

Vector3D reflect(const Vector3D& vector, const Vector3D& normal) {
    return {vector - (2 * dot(vector, normal) * normal)};
}
Vector3D refract(const Vector3D& vector, const Vector3D& normal, double index_ratio) {
    double cos_theta = -dot(normal, vector);
    double discriminant = 1.0 - std::pow(index_ratio, 2) * (1 - std::pow(cos_theta, 2));
    if (discriminant >= 0.0) {
        return index_ratio * vector + (index_ratio * cos_theta - std::sqrt(discriminant)) * normal;
    }
    else { //total internal reflection
        return reflect(vector, normal);
    }
}
double schlick(double cos_theta, double index_ratio) {
    double r0 = std::pow(((1 - index_ratio) / (1 + index_ratio)), 2);
    return r0 + (1 - r0) * std::pow(1 - cos_theta, 5);
}

std::ostream& operator<<(std::ostream& os, const Material& material) {
    os << material.name;
    if (material.emitting) {
        os << " emitting";
    }
    return os;
}

//Diffuse
Diffuse::Diffuse(Texture* texture, bool emitting)
    :Material{"diffuse", texture, emitting} {}

Ray Diffuse::scatter(const Ray& ray, const Hit& hit) const {
    return {hit.position, random_hemisphere(hit.normal)};
}

//Purely Specular
Specular::Specular(Texture* texture, bool emitting)
    :Material{"specular", texture, emitting} {}

Ray Specular::scatter(const Ray& ray, const Hit& hit) const {
    return {hit.position, reflect(ray.direction, hit.normal)};
}
//Metal
Metal::Metal(Texture* texture, bool emitting, double fuzz)
    :Material{"metal", texture, emitting}, fuzz{fuzz} {
        if (fuzz > 1 || fuzz < 0) {
            throw std::runtime_error("metallic fuzz factor must be between 0 and 1");
        }
    }

Ray Metal::scatter(const Ray& ray, const Hit& hit) const {
    Vector3D reflected = reflect(ray.direction, hit.normal);
    if (fuzz > 0) {
        Vector3D random = random_unit_vector() * fuzz;
        reflected += random;
    }
    return {hit.position, reflected};
}

Glass::Glass(Texture* texture, bool emitting) 
    :Material{"glass", texture, emitting} {}

Ray Glass::scatter(const Ray& ray, const Hit& hit) const {
    auto direction = ray.direction;
    auto normal = hit.normal;
    double n1 = 1.0;
    double n2 = 1.5;

    if (dot(direction, normal) > 0) {
        normal *= -1;
        std::swap(n1, n2);
    }

    double cos_theta = -dot(direction, normal);
    double probability = schlick(cos_theta, n1/n2);

    if (random_double() < probability) {
        auto reflected = reflect(direction, normal);
        return Ray{hit.position, reflected};
    }
    else {
        auto refracted = refract(direction, normal, n1/n2);
        return Ray{hit.position, refracted};
    }
}