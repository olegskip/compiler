#include "lexer.h"

Lexer::Lexer(std::string textToScan_): textToScan(std::move(textToScan_))
{
	symbolTable.addWord("+", TokenType::OPERATOR);
	symbolTable.addWord("-", TokenType::OPERATOR);
	symbolTable.addWord("if", TokenType::KEYWORD);
}

std::shared_ptr<Token> Lexer::getNextToken()
{
	if(currentCharIndex >= textToScan.size())
		return {};

	if(textToScan[currentCharIndex] == ' ' || textToScan[currentCharIndex] == '\t' || textToScan[currentCharIndex] == '\n') {
		if(textToScan[currentCharIndex] == '\n')
			currentLine++;
		currentCharIndex++;
		return getNextToken();
	}

	std::string currentWord = "";

	// if the first char is a digit then it must be a number
	if(isdigit(textToScan[currentCharIndex])) {
		while(isdigit(textToScan[currentCharIndex])) {
			currentWord.push_back(textToScan[currentCharIndex++]);
		}

		return std::make_shared<Integer>(currentWord);
	}
	// if the first char is a letter then it may be either an identifier or a keyword
	else if(isalpha(textToScan[currentCharIndex])) {
		while(isalpha(textToScan[currentCharIndex]) || isdigit(textToScan[currentCharIndex])) {
			currentWord.push_back(textToScan[currentCharIndex++]);
		}

		// if the word is already in the table we can just return it
		if(auto wordInMap = symbolTable.getWord(currentWord); wordInMap) {
			return wordInMap;
		}
		else {
			return symbolTable.addWord(currentWord, TokenType::IDENTIFIER);
		}
	}
	// some words(e.g. "+", ">=") don't contain letter or digits so we read the word until we meet a whitespace
	else {
		while(textToScan[currentCharIndex] != ' ' && textToScan[currentCharIndex] != '\t' && textToScan[currentCharIndex] != '\n') {
			currentWord.push_back(textToScan[currentCharIndex++]);
		}
		if(auto wordInMap = symbolTable.getWord(currentWord); wordInMap) {
			return wordInMap;
		}
		else {
			throwError(currentWord);
		}
	}

	return {};
}

void Lexer::throwError(std::string word)
{
	throw std::invalid_argument("Lexical error at line " + std::to_string(currentLine) + " Couldn't resolve " + word);
}
