#ifndef _H_ARGUMENTS_H_
#define _H_ARGUMENTS_H_

///<summary>
/// USE THIS STRUCT TO PASS ARGUMENTS OF ANY TYPE TO YOUR COMPONENTS
///</summary>

struct Arguments
{
	Arguments() {};
	Arguments(int i) : _i(i) {};
	Arguments(float f) : _f(f) {};
	Arguments(double d) : _d(d) {};
	Arguments(std::string s) : _str(s) {};

	std::string _str;
	int _i;
	float _f;
	double _d;
};
#endif
