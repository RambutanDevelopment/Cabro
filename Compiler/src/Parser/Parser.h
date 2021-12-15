#pragma once 

#include "Lexer/Token.h"

// std
#include <vector>

class Parser
{
private:

public:
    Parser(const std::vector<Token>& tokens);
    ~Parser() {}

    ProgramNode Parse();
};