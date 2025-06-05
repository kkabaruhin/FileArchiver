#pragma once
#include <string>
class ArchiverImp {
public:
	static std::string archiveString(std::string inStr);
	static void archiveFile(std::string filePath);
	static std::string unzip(std::string inStr);
};