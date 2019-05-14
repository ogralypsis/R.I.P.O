#ifndef FACTORY_H
#define FACTORY_H

#include <string>
#include <map>

///<summary>
/// Abstract class for the DerivedCreator
///</summary>
template <class T>
class Creator
{
public:
	virtual ~Creator() {}

	virtual T* Create() = 0;
};

///<summary>
/// Base class for the objects that go into the factoryMap
///</summary>
template <class DerivedType, class BaseType>
class DerivedCreator : public Creator<BaseType>
{
public:
	///<summary>
	/// creates an object of type DerivedType (depends of which object you're calling -> stored in the map)
	///</summary>
	BaseType* Create() {
		return new DerivedType;
	}
};

template <class T>
class Factory
{
public:
	Factory() {}

	///<summary>
	/// adds new name of factory with its factory (constructor) to the map
	///</summary>
	///<param name="id"> name of object </param>
	///<param name="fn"> constructor of the object </param>
	void Register(std::string id, Creator<T>* fn) {
		_functionMap[id] = fn;
	}

	///<summary>
	/// creates object from the factory whose string is id
	///</summary>
	///<param name="id"> object to be created </param>
	T* Create(std::string id) {
		return _functionMap[id]->Create();
	}
	
	///<summary>
	/// clears the map
	///</summary>
	~Factory() {
		_functionMap.clear();
	}

private:
	///<summary>
	/// map of factories
	///</summary>
	std::map<std::string, Creator<T>*> _functionMap;
};
#endif