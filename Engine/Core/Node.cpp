#include "Node.h"

#include "Log.h"

u32 Node::ID = 0;

Node &Node::addChild(Node &node)
{
    if (&node == parent)
        return *this;
    Node t = node;

    if (node.parent)
        node.parent->children.remove(node);

    children.emplace_back(t);

    node.parent = this;
    return children.back();
}

Node &Node::addChild(const std::string &name)
{
    children.emplace_back(name, this);
    return children.back();
}

void Node::removeChild(Node &node)
{
    node.destroy();
}

Node *Node::getChild(const std::string &name)
{
    for (auto &child : children)
    {
        if (child.name == name)
            return &child;
    }
    return nullptr;
}

void Node::setParent(Node *parent)
{
    parent->addChild(*this);
}

void Node::destroy()
{
    ID -= getAllChildrenCount() + 1;
    if (parent)
        parent->children.remove(*this);
}

u32 Node::getAllChildrenCount() const
{
    u32 count = getChildrenCount();

    for (const auto &child : children)
    {
        count += child.getAllChildrenCount();
    }
    return count;
}