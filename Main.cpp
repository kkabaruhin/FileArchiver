#include "FilesArchiverImp.h"
#include <iostream>  
#include <string> 

int main() {
	std::cout << "Enter the path to the folder:" << std::endl;
	std::string path;
	std::cin >> path;
	FilesArchiverImp* filesArchiver = new FilesArchiverImp();
	filesArchiver->archive(path);
}