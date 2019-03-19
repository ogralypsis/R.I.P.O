#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include <json.hpp>

using namespace nlohmann;

class FileReader
{

private:

	static FileReader* _instance;
	json _file;
	FileReader();

public:

	~FileReader();
	static FileReader* getInstance();
	json readFile(std::string fileName);
	
};

