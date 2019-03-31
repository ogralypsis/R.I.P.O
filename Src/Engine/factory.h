#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <map>

template <class T>
class Creator
{
public:
	virtual ~Creator() {}

	virtual T* Create() = 0;
};

template <class DerivedType, class BaseType>
class DerivedCreator : public Creator<BaseType>
{
public:
	BaseType* Create() {
		return new DerivedType;
	}
};

template <class T>
class Factory
{
public:
	Factory() {}

	void Register(std::string id, Creator<T>* fn) {
		_functionMap[id] = fn;
	}

	T* Create(std::string id) {
		return _functionMap[id]->Create();
	}
	
	~Factory() {
		// Just delete everything
		for (auto i : _functionMap) {
			//delete(i).second;
		}
	}

private:
	std::map<std::string, Creator<T>*> _functionMap;
};
#endif