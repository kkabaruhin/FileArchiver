#include "ArchiverImp.h"
#include <string>
#include <iostream>  
#include <fstream>

std::string ArchiverImp::archiveString(std::string inStr) {
	std::string result = "";
	if (inStr == "") return result;

	int currCount = 0;
	char prevSymbol = inStr[0];
	for (char currSymbol : inStr) {
		if (prevSymbol == currSymbol) {
			if (currCount == 9) {
				result += std::to_string(currCount) + currSymbol;
				currCount = 0;
			}
			++currCount;
		}
		else {
			result += std::to_string(currCount) + prevSymbol;
			currCount = 1;
		}
		prevSymbol = currSymbol;
	}
	result += std::to_string(currCount) + prevSymbol;
	return result;
}

void ArchiverImp::archiveFile(std::string filePath) {
	std::ifstream inFile(filePath);
	if (!inFile.is_open()) {
		std::cerr << "File opening error!" << std::endl;
		return;
	}

	std::string outFileName = "Archived" + filePath.substr(filePath.find_last_of("/\\") + 1);
	std::ofstream outFile(filePath.substr(0, filePath.find_last_of("/\\") + 1) + outFileName);

	std::string line;
	while (std::getline(inFile, line)) {
		std::string arcLine = ArchiverImp::archiveString(line);
		outFile << arcLine << std::endl;
	}

	outFile.close();
	inFile.close();
}

std::string ArchiverImp::unzip(std::string inStr) {
	std::string result = "";
	if (inStr == "") return result;

	for (int i = 0; i < inStr.length(); i += 2) {
		result += std::string(inStr[i] - '0', inStr[i + 1]);
	}
	return result;
}