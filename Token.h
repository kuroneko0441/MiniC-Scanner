/* 2017�� 5�� ���ľ�� ���� Scanner �������� */
/* �ۼ���: 2015112105 ���ؿ� */
/* �ۼ���: 2017.15.27 */
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
