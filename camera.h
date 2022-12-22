#pragma once
#include "vector3d.h"
#include "point3d.h"
#include "ray.h"

class Camera {
public:
    Camera(Point3D position, Point3D target, Vector3D up, double fov, double aspect);
    Ray compute_ray(double s, double t) const;
private:
    Point3D position;
    Point3D upper_left_corner;
    Vector3D horizontal, vertical; // vectors along u, v with lengths width, height
};