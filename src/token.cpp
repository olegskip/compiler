#include "token.h"

Token::Token(std::string lexeme_, TokenType tokenType_): lexeme(std::move(lexeme_)), tokenType(tokenType_)
{

}

Integer::Integer(std::string lexeme): Token(lexeme, TokenType::INTEGER), value(std::stoi(lexeme))
{

}
