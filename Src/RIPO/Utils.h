#ifndef UTILS_H
#define UTILS_H

typedef struct Pos {

	Pos (float x, float y, float z): _x(x), _y(y), _z(z){}

	float _x;
	float _y;
	float _z;

};

typedef struct Dir {

	int x;
	int y;
	int z;
};

typedef struct Quat {


	Quat(float w, float x, float y, float z) : _w(w), _x(x), _y(y), _z(z) {}

	float _w;
	float _x;
	float _y;
	float _z;
};



#endif // !UTILS_H


