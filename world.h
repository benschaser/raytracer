#pragma once
#include "point3d.h"
#include "hit.h"
#include "color.h"
#include "object.h"
#include "hitbox.h"
#include <memory>
#include <vector>
#include <optional>

class Ray;
class Object;
class BVH_node;

class World {
public:
    // void add(Point3D center, double radius, Color color, bool emitting);
    void add(std::shared_ptr<Object> object);
    // void add(std::shared_ptr<Sphere> sphere);
    std::optional<Hit> find_nearest(const Ray& ray) const;
    std::optional<Hit> find_nearest_BV(const Ray& ray) const;
    void _find_nearest_BV(const Ray& ray, BVH_node* bvh_node, double& time, Object*& nearest) const;
    void construct_BVH_tree();
    // BVH_node* _construct_BVH_tree(const std::vector<BV> BVH_objects, int& objects_index);
    BVH_node* _construct_BVH_tree(const std::vector<Hitbox*> hitboxes);

    std::vector<std::shared_ptr<Object>> objects;
    std::vector<std::shared_ptr<BVH_node>> BVH_tree;
};
