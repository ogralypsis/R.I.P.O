#include "FileReader.h"

FileReader* FileReader::_instance = nullptr;

FileReader::FileReader()
{
}


FileReader::~FileReader()
{
}

FileReader & FileReader::GetInstance()
{
	if (FileReader::_instance == nullptr) {
		FileReader::_instance = new FileReader();
	}

	return *FileReader::_instance;
}

json FileReader::ReadFile(std::string fileName)
{
	std::fstream i(fileName);

	i >> _file;

	i.close();

	return _file;
}
