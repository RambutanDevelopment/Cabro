#pragma once

// std
#include <string>

enum class TokenType
{
	INTVAL, FLOATVAL, MUL, DIV, ADD, SUB, SEMI
};

class Token
{
private:
	TokenType type;
	std::string value;
public:
	Token(TokenType type)
		: type(type), value("\0")
	{}
	Token(TokenType type, const std::string& value)
		: type(type), value(value)
	{}

	std::string str();
	TokenType getType() const { return type; }
};
