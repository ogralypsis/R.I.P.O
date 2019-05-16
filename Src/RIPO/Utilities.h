#ifndef UTILITIES_H
#define UTILITIES_H


struct Pos {

	Pos(float x, float y, float z) : _x(x), _y(y), _z(z) {};

	// default parameterized constructor
	Pos(): _x(0.0f), _y(0.0f), _z(0.0f)
	{
	};

	// assignment operator modifies object, therefore non-const
	Pos& operator=(const Pos& other)
	{
		_x = other._x;
		_y = other._y;
		_z = other._z;
		return *this;
	}

	float _x;
	float _y;
	float _z;
};

struct Dir {

	Dir(int x, int y, int z) : _x(x), _y(y), _z(z) {};

	// default parameterized constructor
	Dir() : _x(0), _y(0), _z(0)
	{
	};
		
	// assignment operator modifies object, therefore non-const
	Dir& operator=(const Dir& other)
	{
		_x = other._x;
		_y = other._y;
		_z = other._z;
		return *this;
	}


	int _x;
	int _y;
	int _z;
};

struct Quat {

	Quat(float w, float x, float y, float z) : _w(w), _x(x), _y(y), _z(z) {};

	// default parameterized constructor
	Quat() : _w(0.0f), _x(0.0f), _y(0.0f), _z(0.0f)
	{
	};

	// assignment operator modifies object, therefore non-const
	Quat& operator=(const Quat& other)
	{
		_w = other._w;
		_x = other._x;
		_y = other._y;
		_z = other._z;
		return *this;
	}

	float _w;
	float _x;
	float _y;
	float _z;
};



#endif // !UTILITIES_H


