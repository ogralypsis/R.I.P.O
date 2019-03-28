#ifndef FACTORY_H
#define FACTORY_H
#include <string>
#include <map>

#include "Component.h"

template <class T>
class Creator
{
public:
	virtual ~Creator() {}

	virtual T* Create() = 0;
	
	virtual T* Create(std::string arg) = 0;
};

template <class DerivedType, class BaseType>
class DerivedCreator : public Creator<BaseType>
{
public:
	BaseType* Create() {
		return new DerivedType;
	}
	
	BaseType* Create(std::string arg) {
		return new DerivedType(arg);
	}
};

template <class T, class Key>
class Factory
{
public:
	Factory() {}

	void Register(Key id, Creator<T>* fn) {
		_functionMap[id] = fn;
	}

	T* Create(Key id) {
		return _functionMap[id]->Create();
	}
	
	T* Create(Key id, std::string arg) {
		return _functionMap[id]->Create(arg);
	}
	
	~Factory() {
		// Just delete everything
		for (auto i : _functionMap) {
			delete(i).second;
		}
	}

private:
	std::map<Key, Creator<T>*> _functionMap;
};
#endif