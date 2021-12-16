#include "Node.h"

#include <stdexcept>

ConstructNode::ConstructNode(int size, int precedence)
{
    nodes.resize(size);
    precendeceval = precedence;
    for (int i = 0; i < size; i++)
    {
        nodes[i] = std::make_shared<Node>();
    }
}

ConstantNode::ConstantNode(const std::string& value)
    : value(value) 
{
    nodes.resize(0);
}