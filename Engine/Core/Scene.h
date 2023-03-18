#pragma once

#include "Node.h"
#include <glm/glm.hpp>


class Camera;

class Scene
{
public:
    std::list<Node> nodes;
    Camera* camera;
    glm::uvec2 viewport_size;
    bool resized = false;

    Node& addNode(const std::string& name) 
    {
        nodes.emplace_back(name);
        return nodes.back();
    }

    Node& addNode() 
    {
        nodes.emplace_back("untitled " + std::to_string(nodes.size()));
        return nodes.back();
    }

    void removeNode(Node& node)
    {
        nodes.remove(node);
    }

    void clear()
    {
        nodes.clear();
    }

    //glm::mat4 projection;
    //glm::mat4 view;
};