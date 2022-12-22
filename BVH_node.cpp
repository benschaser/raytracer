#include "BVH_node.h"

BVH_node::BVH_node(std::shared_ptr<Hitbox> hitbox, BVH_node* left, BVH_node* right)
    :hitbox{hitbox}, left{left}, right{right} {}


