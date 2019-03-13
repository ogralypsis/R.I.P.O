#include "FileReader.h"



FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

FileReader* FileReader::getInstance()
{
	if (_instance == nullptr) {
		_instance = new FileReader();
	}

	return _instance;
}

json FileReader::readFile(std::string fileName)
{
	std::fstream i(fileName);

	i >> _file;

	i.close();

	return _file;
}
