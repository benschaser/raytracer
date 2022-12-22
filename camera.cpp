#include "camera.h"
#include "constants.h"

Camera::Camera(Point3D position, Point3D target, Vector3D up, double fov, double aspect)
    :position{position} {
        double viewport_width = 2 * tan(fov * (Constants::Pi / 180) / 2);
        double viewport_height = viewport_width / aspect;
        Vector3D w = unit(target - position);
        Vector3D u = unit(cross(w, up));
        Vector3D v = cross(w, u);
        horizontal = u * viewport_width;
        vertical = v * viewport_height;
        upper_left_corner = position + w - (horizontal / 2) - (vertical / 2);
    }
Ray Camera::compute_ray(double s, double t) const {
    Point3D origin = upper_left_corner + s * horizontal + t * vertical;
    Vector3D direction = origin - position;
    return Ray{origin, direction};
}