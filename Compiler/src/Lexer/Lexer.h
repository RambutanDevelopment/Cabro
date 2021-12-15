#pragma once

#include "Token.h"

// std
#include <string>
#include <vector>

class Lexer
{
private:
	std::string fileData;
	const char* charPtr;
public:
	Lexer(const std::string& filePath);

	std::vector<Token> Tokenize();
private:
	Token TokenizeNum();
	bool within(const char* charList);
};