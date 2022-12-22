#pragma once
#include "object.h"
#include "hitbox.h"
#include <vector>

class BVH_node {
public:
    BVH_node(std::shared_ptr<Hitbox> hitbox, BVH_node* left, BVH_node* right);
    ~BVH_node() {}

    std::shared_ptr<Hitbox> hitbox;
    BVH_node* left;
    BVH_node* right;
};