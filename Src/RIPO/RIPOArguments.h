#ifndef _H_RIPOARGUMENTS_H_
#define _H_RIPOARGUMENTS_H_
#include <ArgumentStruct.h>

struct RenderComponentArgs : Arguments 
{
	// default constructors
	RenderComponentArgs() {};

	RenderComponentArgs(std::string args) : mesh(args) {};
	std::string mesh;
};
#endif
