#ifndef LEXER_H
#define LEXER_H

#include <stdexcept>

#include "symbol_table.h"

class Lexer
{
public:
	Lexer(std::string textToScan_);
	Lexer(const Lexer &lexer) = delete;
	Lexer(const Lexer &&lexer) = delete;
	Lexer &operator=(const Lexer &lexer) = delete;

private:
	std::shared_ptr<Token> getNextToken();
	void throwError(std::string word);

	size_t currentLine = 0, currentCharIndex = 0;

	SymbolTable symbolTable;

	const std::string textToScan;
};

#endif // LEXER_H
