#include "hitbox.h"

Hitbox::Hitbox(Point3D p1, Point3D p2)
    :p1{p1}, p2{p2}, object{nullptr} {}
Hitbox::Hitbox(Object* object, Point3D p1, Point3D p2)
    :p1{p1}, p2{p2}, object{object} {}

std::optional<double> Hitbox::intersect(const Ray& ray) const {
    Vector3D invD = 1 / ray.direction;
    Vector3D t0s = (p1 - ray.origin) * invD;
    Vector3D t1s = (p2 - ray.origin) * invD;

    double tmin = max(max(min(t0s.x, t1s.x), min(t0s.y, t1s.y)), min(t0s.z, t1s.z));
    double tmax = min(min(max(t0s.x, t1s.x), max(t0s.y, t1s.y)), max(t0s.z, t1s.z));

    // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
    if (tmax < 0) {
        return {};
    }
    // if tmin > tmax, ray doesn't intersect AABB
    if (tmin > tmax) {
        return {};
    }
    if (tmin < 0) {
        return tmax;
    }
    // std::cout << "Obj Intersect!\n";
    return tmin;

}

Hitbox create_hitbox(const Object* obj) {
    return obj->create_hitbox();
}

Hitbox create_hitbox(std::vector<Hitbox*> boxes) {
    double minX = boxes.at(0)->p1.x;
    double minY = boxes.at(0)->p1.y;
    double minZ = boxes.at(0)->p1.z;
    double maxX = boxes.at(0)->p2.x;
    double maxY = boxes.at(0)->p2.y;
    double maxZ = boxes.at(0)->p2.z;
    // double maxX = objects.at(0).create_BV().p2.z;
    for (auto obj : boxes) {
        // BV bv= obj.create_BV();
        minX = min(minX, obj->p1.x);
        minY = min(minY, obj->p1.y);
        minZ = min(minZ, obj->p1.z);
        maxX = max(maxX, obj->p2.x);
        maxY = max(maxY, obj->p2.y);
        maxZ = max(maxZ, obj->p2.z);
        // maxZ = max(maxZ, bv.p2.z);
    }
    return Hitbox{{minX, minY, minZ}, {maxX, maxY, maxZ}};
}

double max(double a, double b) {
    if (a >= b) {
        return a;
    }
    return b;
}
double min(double a, double b) {
    if (a <= b) {
        return a;
    }
    return b;
}
    