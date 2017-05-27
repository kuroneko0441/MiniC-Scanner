#include "Scanner.h"
#include <iostream>

Scanner::Scanner(std::string fileName):fileName(fileName), lineNum(1), colNum(0) {
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

char Scanner::getChar() {
	//get character from file
	char c = file.get();
	if(c == '\n') {
		//save & reset colNum, add lineNum
		lastCol = colNum;
		colNum = 0;
		lineNum++;
	} else {
		//add lineNum
		colNum++;
	}
	return c;
}

void Scanner::ungetChar() {
	if(colNum == 1) {
		colNum = lastCol;
		lineNum--;
	} else {
		colNum--;
	}
	file.unget();
}

Token Scanner::scanToken() {
	int index;
	char c;
	std::string input;
	Token token;
	token.number = tNull;

	do {
		// skip spaces
		while(isspace(c = getChar()));

		token.lineNum = lineNum;
		token.colNum = colNum;
		token.id = c;
		token.value = '0';

		if(isSuperLetter(c)) {
			// symbols & identifiers

		} else if(c == '\'') {
			// character literal

		} else if(isDigit(c)) {
			// integer & double literal

		} else if(c == '\"') {
			// string literal

		} else {
			// operators
			switch(c) {
			case '/':
			{
				c = getChar();
				if(c == '/') {
					// single-line comment
					do {
						c = getChar();
					} while(c != '\n');
				} else if(c == '*') {
					c = getChar();
					if(c == '*') {
						// documented comment
						do {
							if((c = getChar()) == '*') {
								if(getChar() == '/')
									break;
								ungetChar();
							}
							std::cout << c;
						} while(c != '/');
					} else {
						// multi-line comment
						do {
							if((c = getChar()) == '*') {
								if(getChar() == '/')
									break;
								ungetChar();
							}
						} while(c != '/');
					}
				} else if(c == '=') {
					// /= opertor (divide-assign)
					token.number = tDivideAssign;
				} else {
					// / opertor (divide)
					token.number = tDivide;
					ungetChar();
				}
				break;
			}
			case '!':
			{
				c = getChar();
				if(c == '=') {
					token.number = tNotequal;
					token.id += '=';
				} else {
					token.number = tNot;
					ungetChar();
				}
				break;
			}
			case '%':
			{
				c = getChar();
				if(c == '=') {
					token.number = tRemaiderAssign;
					token.id += '=';
				} else {
					token.number = tRemainder;
					ungetChar();
				}
				break;
			}
			case '&':
			{
				c = getChar();
				if(c == '&') {
					token.number = tAnd;
					token.id += '&';
				} else {
					printError(1);
					ungetChar();
				}
				break;
			}
			case '*':
			{
				c = getChar();
				if(c == '=') {
					token.number = tMuliplyAssign;
					token.id += '=';
				} else {
					token.number = tMuliply;
					ungetChar();
				}
				break;
			}
			case '+':
			{

				c = getChar();
				if(c == '=') {
					token.number = tPlusAssign;
					token.id += '=';
				} else {
					token.number = tPlus;
					ungetChar();
				}
				break;
			}
			case '-':
			{

				c = getChar();
				if(c == '=') {
					token.number = tMinusAssign;
					token.id += '=';
				} else {
					token.number = tMinus;
					ungetChar();
				}
			}
			case '<':
			{
				c = getChar();
				if(c == '=') {
					token.number = tLessEqual;
					token.id += '=';
				} else {
					token.number = tLess;
					ungetChar();
				}
				break;
			}
			case '=':
			{
				c = getChar();
				if(c == '=') {
					token.number = tEqual;
					token.id += '=';
				} else {
					token.number = tAssign;
					ungetChar();
				}
				break;
			}
			case '>':
			{
				c = getChar();
				if(c == '=') {
					token.number = tGreatEqual;
					token.id += '=';
				} else {
					token.number = tGreat;
					ungetChar();
				}
				break;
			}
			case '|':
			{
				c = getChar();
				if(c == '|') {
					token.number = tOr;
					token.id += '|';
				} else {
					printError(2);
					ungetChar();
				}
				break;
			}
			case '(':
			{
				token.number = tLeftParen;
				break;
			}
			case ')':
			{
				token.number = tRightParen;
				break;
			}
			case ',':
			{
				token.number = tComma;
				break;
			}
			case ':':
			{
				token.number = tColon;
				break;
			}
			case ';':
			{
				token.number = tSemicolon;
				break;
			}
			case '[':
			{
				token.number = tLeftBracket;
				break;
			}
			case ']':
			{
				token.number = tRightBracket;
				break;
			}
			case '{':
			{
				token.number = tlbrace;
				break;
			}
			case '}':
			{
				token.number = trbrace;
				break;
			}
			case EOF:
			{
				token.number = tEOF;
				return token;
			}
			default: break;
			}
		}

	} while(token.number == tNull);

	return token;
}

void Scanner::scanAll() {
	Token token;
	while((token = scanToken()).number != tEOF) {
		printToken(token);
	}
}
