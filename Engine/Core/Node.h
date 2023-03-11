#pragma once

#include <list>
#include <string>
#include "Core.h"
#include "ECS/Entity.h"

class Node : public Entity
{
public:
    std::string name;

private:
    std::list<Node> children;
    Node *parent = nullptr;
    u32 id;

public:
Node(const Node& other) {*this = other;}
    Node(const std::string &_name) : name(_name), id(ID++) {}
    Node(const std::string &_name, Node *_parent) : name(_name), parent(_parent), id(ID++) {}

    Node &addChild(Node &node);
    Node &addChild(const std::string &name);
    void removeChild(Node &node);

    std::list<Node> &getChildren() { return children; }
    Node *getParent() { return parent; }
    Node *getChild(const std::string &name);

    void setParent(Node *parent);

    void destroy();

    bool operator==(const Node &other) const { return id == other.id; }
    u32 getChildrenCount() const { return children.size(); }
    u32 getAllChildrenCount() const;

private:
    static u32 ID;
};