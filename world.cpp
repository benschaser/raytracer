#include "world.h"
#include "constants.h"
#include "material.h"
#include "object.h"
#include "BVH_node.h"
#include "random.h"

void World::add(std::shared_ptr<Object> object) {
    objects.push_back(object);
}
// void World::add(std::shared_ptr<Sphere> sphere) {
//     objects.push_back(sphere);
// }

std::optional<Hit> World::find_nearest(const Ray& ray) const {
    double time = Constants::Infinity;
    Object* nearest = nullptr;
    for (std::size_t i = 0; i < objects.size(); ++i) {
        std::optional<double> t = objects.at(i)->intersect(ray);
        if (t.has_value() && t.value() < time) {
            nearest = objects.at(i).get();
            time = t.value();
        }
    }
    // for (auto object : objects) {
    //     std::optional<double> t = object->intersect(ray);
    //     if (t.has_value() && t.value() < time) {
    //         nearest = object;
    //         time = t.value();
    //     }
    // }
    if (nearest) {
        Hit hit = nearest->construct_hit(ray, time);
        return hit;
    } else {
        return {};
    }
}

std::optional<Hit> World::find_nearest_BV(const Ray& ray) const { // wrapper function
    double time = Constants::Infinity;
    Object* nearest = nullptr;
    _find_nearest_BV(ray, BVH_tree.at(BVH_tree.size() - 1).get(), time, nearest);

    if (nearest) {
        Hit hit = nearest->construct_hit(ray, time);
        return hit;
    } else {
        return {};
    }
}
void World::_find_nearest_BV(const Ray& ray, BVH_node* bvh_node, double& time, Object*& nearest) const { // recursive tree traversal
    if (!bvh_node->hitbox) {
        std::cout << "no hitbox\n";
        return;
    }

    if (bvh_node->hitbox->object) {
        std::optional<double> time_n = bvh_node->hitbox->object->intersect(ray);
        if (time_n.has_value() && time_n.value() < time) {
            nearest = bvh_node->hitbox->object;
            time = time_n.value();
            
        }
        return;
    }

    if (bvh_node->left && bvh_node->left->hitbox) {
        std::optional<double> test_left = bvh_node->left->hitbox->intersect(ray);
        if (test_left.has_value()) {
            _find_nearest_BV(ray, bvh_node->left, time, nearest);
        }
    }
    if (bvh_node->right && bvh_node->right->hitbox) {
        std::optional<double> test_right = bvh_node->right->hitbox->intersect(ray);
        if (test_right.has_value()) {
            _find_nearest_BV(ray, bvh_node->right, time, nearest);
        }
    }
}
// top down construction
void World::construct_BVH_tree() {
    std::vector<Hitbox*> hitboxes;
    // std::cout << "init tree\n";
    for (auto obj : objects) {
        Hitbox hitbox = obj.get()->create_hitbox();
        hitbox.object = obj.get();
        Hitbox* hitbox_ptr = new Hitbox(hitbox);
        hitboxes.push_back(hitbox_ptr);
    }
    int hitbox_index = 0;
    BVH_node* b = _construct_BVH_tree(hitboxes);
}

// top down construction
BVH_node* World::_construct_BVH_tree(const std::vector<Hitbox*> hitboxes) {
    if (hitboxes.size() == 1) {
        Hitbox hitbox = *hitboxes.at(0);
        // hitbox.object = objects.at(hitbox_index).get();
        // ++hitbox_index;
        BVH_node node = {std::make_shared<Hitbox>(hitbox), nullptr, nullptr};
        std::shared_ptr node_ptr = std::make_shared<BVH_node>(node);
        BVH_tree.push_back(node_ptr);
        return node_ptr.get();
    }
    Hitbox surrounding = create_hitbox(hitboxes);
    // Hitbox* surrounding_ptr = new Hitbox(surrounding);
    
    std::size_t mid = hitboxes.size() / 2;
    std::vector<Hitbox*> bv1{std::begin(hitboxes), std::begin(hitboxes) + mid};
    std::vector<Hitbox*> bv2{std::begin(hitboxes) + mid, std::end(hitboxes)};

    BVH_node node = {std::make_shared<Hitbox>(surrounding), _construct_BVH_tree(bv1), _construct_BVH_tree(bv2)};
    std::shared_ptr node_ptr = std::make_shared<BVH_node>(node);
    BVH_tree.push_back(node_ptr);
    return node_ptr.get();
}


