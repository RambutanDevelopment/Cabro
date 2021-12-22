#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

// std
#include <iostream>
#include <vector>

int main()
{
	Lexer lexer("/mnt/c/Dev/Cabro/test.x");
	std::vector<Token> tokens = lexer.Tokenize();
	Parser parser(tokens);
	std::shared_ptr<Node> node = parser.Parse();
	
	node->print();
	for (std::shared_ptr<Node> current = node; ;)
	{
		for (std::shared_ptr<Node> currentRight = current->flink(1); ; )
		{
			if (currentRight->flink(1) == nullptr) break;
			currentRight->print(); 
			currentRight = currentRight->flink(1);
		}
		if (current->flink(0) == nullptr) break;
		current = current->flink(0);
		current->print(); 
	}
}

