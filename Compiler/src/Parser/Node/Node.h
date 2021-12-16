#pragma once

#include <memory>
#include <string>
#include <vector>
#include <iostream>

class Node 
{
public:
    std::vector<std::shared_ptr<Node>> nodes;
    virtual std::shared_ptr<Node> flink(int index) { return nullptr; }
    virtual int precedence() { return 0; }
    virtual void print() { std::cout << "Node" << std::endl; }
    std::shared_ptr<Node> blink;
};

class ConstructNode : public Node
{
public:
    int precendeceval = 0;
    virtual std::shared_ptr<Node> flink(int index) override { return nodes[index]; }
    int precedence() override { return precendeceval; }
    ConstructNode(int size, int precedence);
};

class ConstantNode : public Node
{
public:
    std::string value;
    ConstantNode(const std::string& value);
};

class MulNode : public ConstructNode
{
public:
    MulNode() 
    : ConstructNode(2, 6) {}
    virtual void print() { std::cout << "MulNode" << std::endl; }
};

class DivNode : public ConstructNode
{
public:
    DivNode() 
    : ConstructNode(2, 6) {}
    virtual void print() { std::cout << "DivNode" << std::endl; }
};

class AddNode : public ConstructNode
{
public:
    AddNode() 
    : ConstructNode(2, 5) {}
    virtual void print() { std::cout << "AddNode" << std::endl; }
};

class SubNode : public ConstructNode
{
public:
    SubNode() 
    : ConstructNode(2, 5) {}
    virtual void print() { std::cout << "SubNode" << std::endl; }
};

class IntNode : public ConstantNode
{
public:
    IntNode(const std::string& value) 
    : ConstantNode(value) {}
    virtual void print() { std::cout << "IntNode: " << value << std::endl; }
};

class FloatNode : public ConstantNode
{
public:
    FloatNode(const std::string& value) 
    : ConstantNode(value) {}
    virtual void print() { std::cout << "FloatNode: " << value << std::endl; }
};



