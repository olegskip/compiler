#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <map>
#include <memory>

#include "token.h"

class SymbolTable
{
public:
	std::shared_ptr<Token> addWord(std::string lexeme, TokenType tokenType) noexcept;
	std::shared_ptr<Token> getWord(std::string lexeme) noexcept;

	SymbolTable *createNewTable() noexcept;
	SymbolTable *getPrevTable() noexcept;

private:
	std::map<std::string, std::shared_ptr<Token>> words;

	SymbolTable *prevTable;
};


#endif // SYMBOL_TABLE_H
