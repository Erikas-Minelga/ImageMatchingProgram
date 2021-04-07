#include "FileManager.h"

std::stringstream FileManager :: readFromFile(std::string path)
{
	std::fstream file;
	file.open(path.c_str());

	std::string ln;
	std::stringstream ss;

	while (getline(file,ln))
	{
		ss << ln << "\n";
	}

	file.close();

	return ss;
}

void FileManager :: writeToFile(std::string data, std::string path)
{
	std::fstream file;
	file.open(path.c_str());

	file << data.c_str();

	file.close();
}