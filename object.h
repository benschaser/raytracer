#pragma once
#include <optional>
#include <vector>
#include <memory>
#include "ray.h"
#include "point3d.h"
#include "hit.h"
#include "material.h"

using UV = std::pair<double, double>;
class Hitbox;

class Object {
public:
    Object(std::shared_ptr<Material> material, std::string type);

    virtual std::optional<double> intersect(const Ray& ray) const = 0;
    virtual Hit construct_hit(const Ray& ray, double time) const = 0;
    virtual UV uv(const Hit& hit) const = 0;
    virtual Hitbox create_hitbox() const = 0;

    std::shared_ptr<Material> material;
    std::string type;
};

class Sphere : public Object {
public:
    Sphere(const Point3D& center, double radius, std::shared_ptr<Material> material);

    //return distance if ray intersects
    std::optional<double> intersect(const Ray& ray) const override;
    Hit construct_hit(const Ray& ray, double time) const override;
    UV uv(const Hit& hit) const override;
    Hitbox create_hitbox() const override;

    std::shared_ptr<Material> material;
    Point3D center;
    double radius;
};

class Triangle : public Object {
public:
    Triangle(const Point3D vertex0, const Point3D vertex1, const Point3D vertex2, std::shared_ptr<Material> material);

    std::optional<double> intersect(const Ray& ray) const override;
    Hit construct_hit(const Ray& ray, double time) const override;
    UV uv(const Hit& hit) const override;
    Hitbox create_hitbox() const override;

    Point3D vertex0, vertex1, vertex2;
private:
    Vector3D edge1, edge2, normal;
};

// class BV : public Object {
// public:
//     BV(Point3D p1, Point3D p2);

//     std::optional<double> intersect(const Ray& ray) const override;
//     Hit construct_hit(const Ray& ray, double time) const override;
//     UV uv(const Hit& hit) const override;
//     BV create_BV() const override;
//     Point3D p1, p2;
// };

// // BV createBV(const Sphere& sphere);
// // BV createBV(const Triangle& triangle);
// BV create_BV(const BV left, const BV right);
// BV create_BV(const std::vector<BV> o);