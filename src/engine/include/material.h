#pragma once
#include "color.h"
#include "ray.h"
#include "hit.h"
#include "texture.h"

class Material {
public:
    Material(std::string name, Texture* texture, bool emitting);
    virtual ~Material() {}
    virtual Ray scatter(const Ray& ray, const Hit& hit) const = 0;
    
    std::string name;
    Texture* texture;
    bool emitting;
};

Vector3D reflect(const Vector3D& vector, const Vector3D& normal);
Vector3D refract(const Vector3D& vector, const Vector3D& normal, double index_ratio);
double schlick(double cos_theta, double index_ratio);
std::ostream& operator<<(std::ostream& os, const Material& material);

class Diffuse : public Material {
public:
    Diffuse(Texture* texture, bool emitting);
    Ray scatter(const Ray& ray, const Hit& hit) const override;
};

class Specular : public Material {
public:
    Specular(Texture* texture, bool emitting);
    Ray scatter(const Ray& ray, const Hit& hit) const override;
};

class Metal : public Material {
public:
    Metal(Texture* texture, bool emitting, double fuzz);
    Ray scatter(const Ray& ray, const Hit& hit) const override;
private:
    double fuzz;
};

class Glass : public Material {
public:
    Glass(Texture* texture, bool emitting);
    Ray scatter(const Ray& ray, const Hit& hit) const override;
};
