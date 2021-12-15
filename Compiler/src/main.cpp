#include "Lexer/Lexer.h"

// std
#include <iostream>
#include <vector>

int main()
{
	Lexer lexer("/mnt/c/Dev/XCompiler/test.x");

	std::vector<Token> tokens = lexer.Tokenize();
	for (auto token : tokens)
	{
		std::cout << token.str() << std::endl;
	}
}