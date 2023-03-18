#pragma once

#include <string>
#include "ECS/Entity.h"

class Node : public Entity
{
public:
    std::string name;

    Node(const std::string &title) : name(title) {}
};