#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class TokenType
{
	OPERATOR = 256,
	INTEGER,
	KEYWORD,
	IDENTIFIER
};

class Token
{
public:
	Token(std::string lexeme_, TokenType tokenType_);

	const std::string lexeme;
	const TokenType tokenType;
};

class Integer: public Token
{
public:
	Integer(std::string lexeme);

	const int value;
};

#endif // TOKEN_H
