#include "lexer.h"

Lexer::Lexer(std::string textToScan_): textToScan(std::move(textToScan_))
{
	addWord("+", TokenType::OPERATOR);
	addWord("-", TokenType::OPERATOR);
	addWord("test", TokenType::RESERVED);

	tokens = scan();
}

std::vector<std::shared_ptr<Token>> Lexer::scan()
{
	std::vector<std::shared_ptr<Token>> output;
	for(size_t currentCharIndex = 0; currentCharIndex < textToScan.size(); ) {
		if(textToScan[currentCharIndex] == ' ' || textToScan[currentCharIndex] == '\t' || textToScan[currentCharIndex] == '\n') {
			currentCharIndex++;
			continue;
		}

		std::string currentWord = "";

		if(isdigit(textToScan[currentCharIndex])) {
			while(isdigit(textToScan[currentCharIndex])) {
				currentWord.push_back(textToScan[currentCharIndex++]);
			}

			output.push_back(std::make_shared<Integer>(currentWord));
		}
		else if(isalpha(textToScan[currentCharIndex])) {
			while(isalpha(textToScan[currentCharIndex]) || isdigit(textToScan[currentCharIndex])) {
				currentWord.push_back(textToScan[currentCharIndex++]);
			}

			if(auto wordInMap = words[currentWord]; wordInMap) {
				output.push_back(wordInMap);
			}
			else {
				addWord(currentWord, TokenType::VARIABLE);
				output.push_back(words[currentWord]);
			}
		}
		else {
			while(textToScan[currentCharIndex] != ' ' && textToScan[currentCharIndex] != '\t' && textToScan[currentCharIndex] != '\n') {
				currentWord.push_back(textToScan[currentCharIndex++]);
			}
			if(auto wordInMap = words[currentWord]; wordInMap) {
				output.push_back(wordInMap);
			}
			else {
				throw std::invalid_argument("Lexical error");
			}
		}
	}

	return output;
}

void Lexer::addWord(std::string lexeme, TokenType tokenType) noexcept
{
	words.insert({lexeme, std::make_shared<Token>(lexeme, tokenType)});
}
