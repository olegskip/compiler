/*
 * A translator for simple expressions
 * Tranform infix to postfix
 * Works only with one digit numbers
 */

#include <iostream>
#include <exception>
#include <string>

class Parser
{
public:
	Parser(std::string str_): str(str_)
	{
		expr();
		std::cout << "\n";
	}

private:
	void expr()
	{
		term();
		while(lookaheadIndex < str.size())
		{
			if(str[lookaheadIndex] == '+') {
				match('+');
				term();
				std::cout << "+ ";
			}
			else if(str[lookaheadIndex] == '-') {
				match('-');
				term();
				std::cout << "- ";
			}
			else {
				error();
			}
		}
	}

	void term()
	{
		digit();
		std::cout << str[lookaheadIndex] << " ";
		match(str[lookaheadIndex]);
	}

	void digit()
	{
		if(lookaheadIndex >= str.size())
			error();
		if(!isdigit(str[lookaheadIndex]))
			error();
	}


	void match(char ch)
	{
		if(str[lookaheadIndex] == ch) {
			lookaheadIndex++;
		}
		else {
			error();
		}
	}

	void error()
	{
		throw std::logic_error("Syntax error");
	}

	size_t lookaheadIndex = 0;
	std::string str;
};


int main()
{
	const std::string str = "1+2-3";
	Parser parser(str);

	return 0;
}
