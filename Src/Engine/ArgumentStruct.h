#ifndef _H_ARGUMENTS_H_
#define _H_ARGUMENTS_H_
#include "json.hpp"


struct Arguments {

	Arguments() {};
	Arguments(int _i) : i(_i) {};
	Arguments(float _f) : f(_f) {};
	Arguments(double _d) : d(_d) {};
	Arguments(std::string _s) : str(_s) {};

	
	std::string str;
	int i;
	float f;
	double d;

};
#endif
