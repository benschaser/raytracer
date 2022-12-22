#pragma once
#include "vector3d.h"
#include "ray.h"
#include "object.h"

class Hitbox {
public:
    Hitbox(Point3D p1, Point3D p2);
    Hitbox(Object* object, Point3D p1, Point3D p2);
    Hitbox();

    std::optional<double> intersect(const Ray& ray) const;
    
    Point3D p1, p2;
    Object* object;
};

Hitbox create_hitbox(const Object* obj);
Hitbox create_hitbox(std::vector<Hitbox*> boxes);

double max(double a, double b);
double min(double a, double b);