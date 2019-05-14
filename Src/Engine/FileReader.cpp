#include "FileReader.h"
#include <fstream>

FileReader* FileReader::_instance = nullptr;

FileReader::FileReader() {}

FileReader::~FileReader() {}

FileReader* FileReader::GetInstance()
{
	// creates instance if it has not yet been created
	// returns it
	if (_instance == nullptr) {
		_instance = new FileReader();
	}

	return _instance;
}

json FileReader::ReadFile(std::string fileName)
{
	json file;

	// opens json file and reads
	std::fstream i(fileName);

	i >> file;

	// closes file
	i.close();

	// returns file read
	return file;
}
