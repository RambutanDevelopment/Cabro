#include "Token.h"

const char* tokenStrings[] = {
	"INTVAL", "FLOATVAL", "MUL", "DIV", "ADD", "SUB", "SEMI"
};

std::string Token::str()
{
	std::string tokenStr(tokenStrings[(int)type]);
	if (value[0] != '\0') tokenStr.append("::").append(value);
	return tokenStr;
}