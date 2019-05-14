#ifndef FILEREADER_H
#define FILEREADER_H
#include <json.hpp>

using namespace nlohmann;

class FileReader
{
public:
	~FileReader();

	///<summary>
	/// creates the instance or returns one already created. necessary for the singleton pattern
	///</summary>
	static FileReader* GetInstance();

	///<summary>
	/// reads json file and returns the file
	///</summary>
	///<param name="fileName">the name/path of the file</param>
	json ReadFile(std::string fileName);

private:
	///<summary>
	/// keep the constructor private for the singleton pattern
	///</summary>
	FileReader();

	///<summary>
	/// _instance of the singleton
	///</summary>
	static FileReader* _instance;
};
#endif
