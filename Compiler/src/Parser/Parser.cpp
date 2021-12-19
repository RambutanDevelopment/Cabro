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

<<<<<<< Updated upstream
=======
using typeIndex = std::pair<TokenType, int>;

>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
=======
std::vector<typeIndex> PairArray(std::vector<int> list1, std::vector<int> list2, TokenType t1, TokenType t2)
{
    std::vector<typeIndex> combinedList;
    for (int i = 0; i < list1.size(); i++)
    {
        combinedList.emplace_back(t1, list1[i]);
    }

    if (combinedList.size() == 0)
    {
        for (int i = 0; i < list2.size(); i++)
        {
            combinedList.emplace_back(t2, list2[i]);
        }
    }
    else 
    {
        for (int i = 0; i < list2.size(); i++)
        {
            for (int k = 0, j = 0; k < combinedList.size(); k++)
            {
                if (list2[i] < list1[k]) continue;
                else if (list2[i] > list1[k]) 
                {
                    //This looks cursed WTF
                    combinedList.emplace(combinedList.begin() + k + ++j, t2, list2[i]);
                }
            }
        }
    }
    return combinedList;
}

>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
=======
    auto divmulvals = PairArray(vals[0], vals[1], types[0], types[1]);
    auto addsubvals = PairArray(vals[2], vals[3], types[2], types[3]);

>>>>>>> Stashed changes
    std::shared_ptr<Node> node1;
    int j = -1, k = -1;
    
    for (int i = 0, current_prec = 0; i < 4; i++)
    {
<<<<<<< Updated upstream
        if (vals[i].size()) {
=======
        if (vals[i].size()) 
        {
>>>>>>> Stashed changes
            if (vals[i][vals[i].size() - 1] > j) 
            {
                j = vals[i][vals[i].size() - 1]; 
                k = (int) types[i];
            }
        }
<<<<<<< Updated upstream
        if (j != -1 && map_prec[types[i]] < current_prec) break; 
    }

=======
        /*Checks if j doesn't have a value 
        and if so and the last precedence (prec) is 
        lower than that of the type, then exit the loop */
        if (j != -1 && map_prec[types[i]] < current_prec) break; 
    }

    for (int i = 0, current_prec = 0; i < 2; i++)
    {
        switch(i)
        {
            case 0:
                
            case 1:   

        }
        /*Checks if j doesn't have a value 
        and if so and the last precedence (prec) is 
        lower than that of the type, then exit the loop */
        if (j != -1 && map_prec[types[i * 2]] < current_prec) break; 
    }

>>>>>>> Stashed changes
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

<<<<<<< Updated upstream
=======


>>>>>>> Stashed changes
