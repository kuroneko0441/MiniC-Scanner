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
	case 3:
		//|| error
		std::cout << "next character must be \'\n";
		break;
	case 4:
		//|| error
		std::cout << "string must be end in line \n";
		break;
	default: break;
	}
}

void Scanner::printToken(Token t) {
	std::cout << "Token -----> " << symbolName[t.number] << " ";
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
		token.value = '0';

		if(isSuperLetter(c)) {
			// symbols & identifiers
			
			do {
				input += c;
				c = getChar();
			} while(isSuperLetter(c) || isDigit(c));
			ungetChar();
			
			// find the identifier in the keyword table
			for(index = 0; index < KEYWORD_SIZE; index++)
				if(!input.compare(keyword[index]))
					break;
			if(index < KEYWORD_SIZE) {	// found, keyword exit
				token.number = keywordNum[index];
			} else {					// not found, identifier exit
				token.number = tIdentifier;
				token.value = input;
			}
		} else if(c == '\'') {
			// character literal

			token.number = tCharacter;
			c = getChar();
			token.value = c;
			
			// escape character
			if(c == '\\') 
				token.value += getChar();

			// error
			if(getChar() != '\'') {
				printError(3);
				ungetChar();
				token.number = tNull;
			}
		} else if(isDigit(c)) {
			// integer & double literal

		} else if(c == '\"') {
			// string literal

			token.number = tString;
			token.value = "";

			do {
				c = getChar();
				token.value += c;

				// escape character
				if(c == '\\')
					token.value += getChar();

				// string not end error
				if(c == '\n') {
					printError(4);
					ungetChar();
					token.number = tNull;
					break;
				}
			} while(c != '\"');

			// delete last "
			token.value.pop_back();
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
