#pragma once
#include <string>

class Token {
public:
	/* token string */
	std::string id;

	/* token number */
	int number;

	/* token value */
	std::string value;

	/* file information */
	std::string fileName;
	int lineNum;
	int colNum;
};
