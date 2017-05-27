#include "Scanner.h"

Scanner::Scanner(std::string fileName):fileName(fileName) {
	//open file
	file.open(fileName);
}
