#pragma once 

#include "Lexer/Token.h"
#include "Node/Node.h"

// std
#include <vector>

class Parser
{
private:
    int statementIndex = 0;
    int lastStatement = 0;
    std::vector<Token> tokens;
public:
    Parser(const std::vector<Token>& tokens);
    ~Parser() {}

    std::shared_ptr<Node> Parse();
};