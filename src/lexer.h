#ifndef LEXER_H
#define LEXER_H

#include <vector>
#include <map>
#include <memory>
#include <stdexcept>

#include "token.h"

class Lexer
{
public:
	Lexer(std::string textToScan_);
	Lexer(const Lexer &lexer) = delete;
	Lexer(const Lexer &&lexer) = delete;
	Lexer &operator=(const Lexer &lexer) = delete;

	std::vector<std::shared_ptr<Token>> tokens;

private:
	std::vector<std::shared_ptr<Token>> scan();

	std::map<std::string, std::shared_ptr<Token>> words;
	void addWord(std::string lexeme, TokenType tokenType) noexcept;

	const std::string textToScan;
};

#endif // LEXER_H
