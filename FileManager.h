#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <fstream>
#include <sstream>
#include <string>

class FileManager
{
	public:
		FileManager() {}
		~FileManager() {}

		static std::stringstream readFromFile(std::string path);
		static void writeToFile(std::stringstream data, std::string path);
};

#endif