#include "Lexer.h"

// std
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <cstring>

#define DIGITS "0123456789"

Lexer::Lexer(const std::string& filePath)
{
	std::ifstream file(filePath, std::ios::ate);

	if (!file.is_open())
	{
		throw std::runtime_error("File '" + filePath + "' can't be opened. \n Path incorrect?");
	}

	size_t size = file.tellg(); // gets file size

	file.seekg(0); // sets index of string to 0

	fileData.resize(size); // resizes string to file size
	file.read(fileData.data(), size); // reads data to string

	charPtr = fileData.data(); // c string (char*)
}

std::vector<Token> Lexer::Tokenize()
{
	std::vector<Token> tokens;
	while (*charPtr != '\0') // '\0' is end of file
	{
		if (*charPtr == 32 || *charPtr == '\n' || *charPtr == '\r') // 32 is ascii for a space
		{
			charPtr++; // gets next char, incrementing address to get next char bc its a pointer
		}
		else if (*charPtr == ';')
		{
			tokens.emplace_back(TokenType::SEMI); // basically "push" but it constructs new class instead of copy
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
		else if (within(DIGITS)) // checks if char is digit
		{
			tokens.emplace_back(TokenizeNum());
		}
		else
		{
			std::string errormsg("Invalid Char: ");
			errormsg.push_back(*charPtr); // Copies to errormsg var
			throw std::runtime_error(errormsg);
		}
	}
	return tokens;
}

Token Lexer::TokenizeNum() // generates number
{
	std::string buf; // stores number generated
	bool dot = false;

	// "strcat()" combines 2 c strings
	for (; within(DIGITS) || within("."); charPtr++) // checks if char is a digit or a dot, gets next char if true
	{
		buf.push_back(*charPtr); //
		if (*charPtr == '.') // checks if two dots
		{
			if (dot)
			{
				throw std::runtime_error("you have two dots you foolish, incompetent nutcase"); // Might make a function that displays where the invalid char is
			}
			dot = true;
		}
	}

	if (dot)
	{
		return Token(TokenType::FLOATVAL, buf); // returns float if dot is in it
	}
	else
	{
		return Token(TokenType::INTVAL, buf); // returns integer otherwise
	}
}

bool Lexer::within(const char* charList) // char gets checked, returns true if in charlist
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
