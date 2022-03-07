#include "symbol_table.h"

std::shared_ptr<Token>  SymbolTable::addWord(std::string lexeme, TokenType tokenType) noexcept
{
	words.insert({lexeme, std::make_shared<Token>(lexeme, tokenType)});

	return words[lexeme];
}

std::shared_ptr<Token> SymbolTable::getWord(std::string lexeme) noexcept
{
	auto token = words[lexeme];
	if(!prevTable || token)
		return token;
	else
		return prevTable->getWord(lexeme);
}

SymbolTable *SymbolTable::createNewTable() noexcept
{
	SymbolTable *newTable = new SymbolTable();
	newTable->prevTable = this;
	
	return newTable;
}

SymbolTable *SymbolTable::getPrevTable() noexcept
{
	return prevTable;
}
