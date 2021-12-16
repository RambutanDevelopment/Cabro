#pragma once 

#include "Lexer/Token.h"
#include "Node/Node.h"

// std
#include <vector>

class Parser
{
private:
    int statement = 0;
public:
    Parser(const std::vector<Token>& tokens);
    ~Parser() {}

    std::shared_ptr<Node> Parse();
};