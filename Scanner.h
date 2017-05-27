#pragma once
#include <fstream>
#include "Token.h"

class Scanner {
private:
	static const int SYMBOL_SIZE = 55;
	static const int KEYWORD_SIZE = 16;
	const enum Symbol {
		tNull = -1,
		tIdentifier, tCharacter, tInteger, tDouble, tString,

		tLeftParen, tRightParen, tlbrace, trbrace, tLeftBracket, tRightBracket,

		tPlus, tMinus, tMuliply, tDivide, tRemainder,
		tAssign, tPlusAssign, tMinusAssign, tMuliplyAssign, tDivideAssign, tRemaiderAssign,
		tIncrement, tDecrement,

		tAnd, tOr, tNot,
		tEqual, tNotequal, tLess, tGreat, tLessEqual, tGreatEqual,
		tComma, tSemicolon, tColon, tEOF,

		tQuote, tDoubleQuote,

		tconst,
		tvoid, tchar, tint, tdouble,
		tif, telse,
		tfor, twhile, tdo, tgoto, tswitch, tcase, tbreak, tdefault,
		treturn
	};
	const char* symbolName[SYMBOL_SIZE] = {
		"identifier","Character","Integer","Double","String",

		"(",")","{","}","[","]",

		"+","-","*","/","%",
		"=","+=","-=","*=","/=","%=",
		"++","--",

		"&&","||","!",
		"==","!=","<",">","<=",">=",
		",",";",":","EOF",

		"\'","\"",

		"const",
		"void","char","int","double",
		"if","else",
		"for","while","do","goto","switch","case","break","default",
		"return"
	};
	const char* keyword[KEYWORD_SIZE] = {
		"const",
		"void","char","int","double",
		"if","else",
		"for","while","do","goto","switch","case","break","default",
		"return"
	};
	Symbol keywordNum[KEYWORD_SIZE] = {
		tconst,
		tvoid, tchar, tint, tdouble,
		tif, telse,
		tfor, twhile, tdo, tgoto, tswitch, tcase, tbreak, tdefault,
		treturn
	};

private:
	/* file name */
	std::string fileName;
	/* file stream */
	std::ifstream file;

	/* lineNum, colNum managed by Scanner class */
	int lineNum;
	int colNum;
	/* saved column number for ungetting '\n' */
	int lastCol;
public:
	/* initializing file name, file stream */
	Scanner(std::string fileName);

private:
	/* print an error with given code */
	void printError(int errorCode);
	/* print a token */
	void printToken(Token t);
	/* returns true if letter is alphabet or _ */
	bool isSuperLetter(char letter);
	/* returns true if letter is digit ('0' ~ '9') */
	bool isDigit(char letter);
	/* get hex value from character, returns -1 if not */
	int hexValue(char hex);
	/* read character from file, setting colNum & lineNum */
	char getChar();
	/* retract character into file, setting colNum & lineNum */
	void ungetChar();
	/* scan & return 1 Token */
	Token scanToken();

public:
	/* start scanning from first character */
	void scanAll();

};