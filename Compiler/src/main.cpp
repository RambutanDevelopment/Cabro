#include "Lexer/Lexer.h"
#include "Parser/Parser.h"

// std
#include <iostream>
#include <vector>

int main()
{
	Lexer lexer("/mnt/c/Dev/Cabro/test.x");

	std::vector<Token> tokens = lexer.Tokenize();
	for (auto token : tokens)
	{
		std::cout << token.str() << std::endl;
	}

	Parser parser(tokens);
}