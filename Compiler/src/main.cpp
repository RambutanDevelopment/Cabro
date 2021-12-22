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
	node->flink(0)->print();
	for (std::shared_ptr<Node> current = node; ; )
	{
		if (current->flink(1) == nullptr) break;
		current->print(); 
		current = current->flink(1);
	}
}

//Print with double array counter func (recursive calling, with pos info)