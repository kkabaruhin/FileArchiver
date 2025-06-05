#pragma once
#include <string>

class FilesArchiver {
public:
	virtual void archive(std::string path) = 0;
};