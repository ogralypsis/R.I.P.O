#ifndef FACTORY_H
#define FACTORY_H
#include <string>
#include <map>

#include "Component.h"

template <class T>
class Creator
{
public:
	virtual ~Creator();
	virtual T* Create() = 0;
};

template <class DerivedType, class BaseType>
class DerivedCreator : public Creator<BaseType>
{
public:
	BaseType* Create();
};

template <class T, class Key>
class Factory
{
public:
	static Factory* getInstance();

	void Register(Key id, Creator<T>* fn);

	T* Create(Key id);

	~Factory();

private:
	Factory();

	static Factory* _instance;

	std::map<Key, Creator<T>*> _functionMap;
};

#endif