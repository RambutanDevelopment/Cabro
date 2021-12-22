#include "Parser.h"

#include "Utils/Utils.h"

// std
#include <iostream>
#include <unordered_map>

// Parser constructor, does nothing currently
Parser::Parser(const std::vector<Token>& tokens)
    : tokens(tokens)
{

}

// Map of precedences 
std::unordered_map<TokenType, int> map_prec = 
{
    {TokenType::ADD, 5},
    {TokenType::SUB, 5},
    {TokenType::MUL, 6},
    {TokenType::DIV, 6},
    {TokenType::SEMI, 100} // So no seg fault when accessing at a semicolon token
};

// Struct of type, int and int
struct typeIndex
{
    TokenType type;
    int statementIndex, constructsIndex;
    typeIndex() 
        : type(TokenType::SEMI), statementIndex(-1), constructsIndex(-1)
    {}
    typeIndex(TokenType type, int statementIndex, int constructsIndex)
      : type(type), statementIndex(statementIndex), constructsIndex(constructsIndex)
    {}
};

// Detemines the groups of tokens, and their indexes, as well as returning the data for the first node in tree
std::pair<std::vector<typeIndex>, typeIndex> lookup1(std::vector<Token> tokens, TokenType* types, size_t size)
{
    std::vector<typeIndex> vals;
    vals.resize(0);
    typeIndex node1data{TokenType::SEMI, -1, -1};  

    for (int i = 0; i < tokens.size(); i++)
    {
        if (within(tokens[i].getType(), types, size))
        {
            vals.emplace_back(tokens[i].getType(), i, vals.size());
            if (map_prec[node1data.type] >= map_prec[tokens[i].getType()]) 
            {
                node1data = {tokens[i].getType(), i, vals.size() - 1};
            }
        }
    }

    return {vals, node1data};
}

void buildRightNodes(std::shared_ptr<Node> node, const std::vector<typeIndex>& indexes, typeIndex nodeStart, size_t quitAt)
{
    if (nodeStart.constructsIndex + 1 >= quitAt) return;

    switch(indexes[nodeStart.constructsIndex + 1].type)
    {
        case TokenType::ADD: 
            node->setNode(std::make_shared<AddNode>(), 1);
            break;
        case TokenType::SUB: 
            node->setNode(std::make_shared<SubNode>(), 1);
            break;
        case TokenType::MUL: 
            node->setNode(std::make_shared<MulNode>(), 1);
            break;
        case TokenType::DIV: 
            node->setNode(std::make_shared<DivNode>(), 1);
            break;
        default:   
            node->setNode(nullptr, 1);
            break;
    }

    buildRightNodes(node->flink(1), indexes, indexes[nodeStart.constructsIndex + 1], quitAt);
}

typeIndex buildLeftNode(std::shared_ptr<Node> node, const std::vector<typeIndex>& indexes, typeIndex nodeStart)
{
    typeIndex leftNodeData(TokenType::SEMI, -1, -1);
    for (int i = 0; indexes[i].constructsIndex < nodeStart.constructsIndex; i++)
    {
        if (map_prec[leftNodeData.type] >= map_prec[indexes[i].type]) leftNodeData = indexes[i];
    }

    switch(leftNodeData.type)
    {
        case TokenType::ADD: 
            node->setNode(std::make_shared<AddNode>(), 0);
            break;
        case TokenType::SUB: 
            node->setNode(std::make_shared<SubNode>(), 0);
            break;
        case TokenType::MUL: 
            node->setNode(std::make_shared<MulNode>(), 0);
            break;
        case TokenType::DIV: 
            node->setNode(std::make_shared<DivNode>(), 0);
            break;
        default:   
            node->setNode(nullptr, 0);
            break;
    }

    return leftNodeData;
}

//Takes two lists of different tokens and splices them together
/* std::vector<typeIndex> PairArray(std::vector<int> list1, std::vector<int> list2, TokenType t1, TokenType t2)
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
} */

// Returns the first node of a statements AST
std::shared_ptr<Node> Parser::Parse()
{
    // Setting up statements
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

    //Lookup pass 1 (gets first node in the parse tree)
    TokenType types[4] = {TokenType::MUL, TokenType::DIV, TokenType::ADD, TokenType::SUB};

    auto vals = lookup1(statement, types, 4);

    std::shared_ptr<Node> node1;

    switch (vals.second.type)
    {
        case TokenType::ADD: 
            node1 = std::make_shared<AddNode>();
            break;
        case TokenType::SUB: 
            node1 = std::make_shared<SubNode>();
            break;
        case TokenType::MUL: 
            node1 = std::make_shared<MulNode>();
            break;
        case TokenType::DIV: 
            node1 = std::make_shared<DivNode>();
            break;
        default:   
            return nullptr;
            break;
    }

    // Second lookup pass (determines the construct nodes that come from the first node)
    std::shared_ptr<Node> current = node1;
    typeIndex currentData = vals.second;
    size_t quitAt = vals.first.size();
    while (true)
    {
        buildRightNodes(current, vals.first, currentData, quitAt);
        quitAt = currentData.constructsIndex;
        currentData = buildLeftNode(current, vals.first, currentData);
        if (current->flink(0) == nullptr) break;
        current = current->flink(0); 
    }

    return node1;
}


