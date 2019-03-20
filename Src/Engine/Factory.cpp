#include "Factory.h"


template<class T>
Creator<T>::~Creator()
{
}


template <class DerivedType, class BaseType>
BaseType* DerivedCreator<DerivedType, BaseType>::Create()
{
	return new DerivedType;
}


template<class T, class Key>
Factory<T, Key>* Factory<T, Key>::getInstance()
{
	if (_instance == nullptr) {
		_instance = new Factory();
	}
	return _instance;
}

template<class T, class Key>
void Factory<T, Key>::Register(Key id, Creator<T>* fn)
{
	_functionMap[id] = fn;
}

template<class T, class Key>
T * Factory<T, Key>::Create(Key id)
{
	return _functionMap[id]->Create();
}

template<class T, class Key>
Factory<T, Key>::Factory() {
}

template<class T, class Key>
Factory<T, Key>::~Factory()
{
	// Just delete everything
	for (auto i : _functionMap) {
		delete(*i).second;
	}
}