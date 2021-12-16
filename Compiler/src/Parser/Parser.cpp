#include "Parser.h"

// std
#include <iostream>

Parser::Parser(const std::vector<Token>& tokens)
{
    std::shared_ptr<MulNode> mulNode = std::make_shared<MulNode>();
    mulNode->blink = nullptr;
    mulNode->nodes[0] = std::make_shared<IntNode>("8");
    mulNode->flink(0)->blink = mulNode;
    mulNode->nodes[1] = std::make_shared<DivNode>();
    mulNode->nodes[1]->blink = mulNode;
    mulNode->flink(1)->nodes[0] = std::make_shared<IntNode>("9");
    mulNode->flink(1)->nodes[1] = std::make_shared<IntNode>("3");
    mulNode->print();
    mulNode->flink(0)->print();
    mulNode->flink(1)->print();
    mulNode->flink(1)->flink(0)->print();
    mulNode->flink(1)->flink(1)->print(); 
}
