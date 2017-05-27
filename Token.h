#pragma once
#include <string>

class Token {
public:
	/* token number */
	int number;

	/* token value */
	std::string value;

	/* file information */
	std::string fileName;
	int lineNum;
	int colNum;
};
