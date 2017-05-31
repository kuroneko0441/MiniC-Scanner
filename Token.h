/* 2017년 5월 형식언어 수업 Scanner 구현과제 */
/* 작성자: 2015112105 이준영 */
/* 작성일: 2017.15.27 */
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
