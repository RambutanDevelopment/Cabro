#include "Parser.h"

// std
#include <iostream>
#include <unordered_map>

Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens)
{

}

std::unordered_map<TokenType, int> map_prec = 
{
    {TokenType::ADD, 5},
    {TokenType::SUB, 5},
    {TokenType::MUL, 6},
    {TokenType::DIV, 6},
};

std::vector<std::vector<int>> lookup1(const std::vector<Token>& tokens, TokenType* types, size_t size)
{
    std::vector<std::vector<int>> vals(size);

    for (int i = 0; i < size; i++)
    {
        vals[i].resize(0);
    }

    for (int i = 0; i < tokens.size(); i++)
    {
        for (int j = 0; j < size; j++) 
        {
            if (tokens[i].getType() == types[j]) 
            {
                vals[j].push_back(i);
            }
        }
    }

    return vals;
}

std::shared_ptr<Node> Parser::Parse()
{
    std::vector<Token> statement;

    for (int i = lastStatement; ;i++)
    {
        if (i == tokens.size()) return nullptr;
        if (tokens[i].getType() == TokenType::SEMI) 
        {
            i++;
            lastStatement = i;
            break;
        }
        statement.push_back(tokens[i]);
    }

    statementIndex++;

    TokenType types[4] = {TokenType::MUL, TokenType::DIV, TokenType::ADD, TokenType::SUB};

    auto vals = lookup1(statement, types, 4);

    std::shared_ptr<Node> node1;
    int j = -1, k = -1;
    
    for (int i = 0, current_prec = 0; i < 4; i++)
    {
        if (vals[i].size()) {
            if (vals[i][vals[i].size() - 1] > j) 
            {
                j = vals[i][vals[i].size() - 1]; 
                k = (int) types[i];
            }
        }
        if (j != -1 && map_prec[types[i]] < current_prec) break; 
    }

    switch (k)
    {
        case (int) TokenType::ADD: 
            node1 = std::make_shared<AddNode>();
            break;
        case (int) TokenType::SUB: 
            node1 = std::make_shared<SubNode>();
            break;
        case (int) TokenType::MUL: 
            node1 = std::make_shared<MulNode>();
            break;
        case (int) TokenType::DIV: 
            node1 = std::make_shared<DivNode>();
            break;
        default:   
            return nullptr;
            break;
    }

    return node1;
}

