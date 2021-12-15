#include "Lexer.h"

// std
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cstring>

#define DIGITS "0123456789"
#define DOTDIGIT "0123456789."

Lexer::Lexer(const std::string& filePath)
{
	std::ifstream file(filePath, std::ios::ate);

	if (!file.is_open())
	{
		throw std::runtime_error("Failed to open file: " + filePath);
	}

	size_t size = file.tellg();

	file.seekg(0);

	fileData.resize(size);
	file.read(fileData.data(), size);

	charPtr = fileData.data();
}

std::vector<Token> Lexer::Tokenize()
{
	std::vector<Token> tokens;
	while (*charPtr != '\0')
	{
		if (*charPtr == 32 || *charPtr == '\n' || *charPtr == '\r')
		{
			charPtr++;
		}
		else if (*charPtr == ';')
		{
			tokens.emplace_back(TokenType::SEMI);
			charPtr++;
		}
		else if (*charPtr == '*')
		{
			tokens.emplace_back(TokenType::MUL);
			charPtr++;
		}
		else if (*charPtr == '/')
		{
			tokens.emplace_back(TokenType::DIV);
			charPtr++;
		}
		else if (*charPtr == '+')
		{
			tokens.emplace_back(TokenType::ADD);
			charPtr++;
		}
		else if (*charPtr == '-')
		{
			tokens.emplace_back(TokenType::SUB);
			charPtr++;
		}
		else if (within(DIGITS))
		{
			tokens.emplace_back(TokenizeNum());
		}
		else
		{
			std::string errormsg("Bad character: ");
			errormsg.push_back(*charPtr);
			throw std::runtime_error(errormsg);
		}
	}
	return tokens;
}

Token Lexer::TokenizeNum()
{
	std::string buf;
	bool dot = false;
	for (; within(DOTDIGIT); charPtr++)
	{
		buf.push_back(*charPtr);
		if (*charPtr == '.')
		{
			if (dot)
			{
				throw std::runtime_error("Cannot have 2 dots in one number.");
			}
			dot = true;
		}
	}
	if (dot)
	{
		return Token(TokenType::FLOATVAL, buf);
	}
	else
	{
		return Token(TokenType::INTVAL, buf);
	}
}

bool Lexer::within(const char* charList)
{
	int length = strlen(charList);
	for (int i = 0; i < length; i++)
	{
		if (charList[i] == *charPtr)
		{
			return true;
		}
	}
	return false;
}
