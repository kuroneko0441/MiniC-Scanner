#include "Scanner.h"
#include <iostream>

Scanner::Scanner(std::string fileName):fileName(fileName) {
	//open file
	file.open(fileName);
}

void Scanner::printError(int errorCode) {
	std::cout << " *** Lexical Error : ";
	switch(errorCode) {
	case 0:
		//default error
		std::cout << "invalid character\n";
		break;
	case 1:
		//&& error
		std::cout << "next character must be &\n";
		break;
	case 2:
		//|| error
		std::cout << "next character must be |\n";
		break;
	default: break;
	}
}

void Scanner::printToken(Token t) {
	std::cout << "Token -----> " << t.id << " ";
	std::cout << "(" << t.number << ", " << t.value << ", " << fileName << ", " << t.lineNum << ", " << t.colNum << ")";
	std::cout << std::endl;
}

bool Scanner::isSuperLetter(char letter) {
	//'a' ~ 'z' + '_'
	return isalpha(letter) || letter == '_';
}

bool Scanner::isDigit(char letter) {
	//'0' ~ '9'
	return letter >= '0' && letter <= '9';
}
