#pragma once
#include "vector3d.h"

double random_double(); //inclusive [0.0 1.0) exclusive 1
double random_double(double min, double max); // [min, max) same inc/exclusivity
Vector3D random_unit_vector();
Vector3D random_hemisphere(const Vector3D& normal);