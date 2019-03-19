#ifndef FACTORY_H
#define FACTORY_H
#include <string>
#include <map>

// Template for a class
template <class T> 

// Pointer to T constructor
T* constructor() {
	return  new T();
}

struct Factory
{
	// Define type of constructor for the map
	typedef void* (*constructor_t)();

	// define type for classes map
	typedef std::map<std::string, constructor_t> map_type;

	map_type m_classes;

	template <class T>

	//Register new class in the map
	void register_class(std::string const& m)
	{
		m_classes.insert(std::make_pair(m, &constructor<T>));
	}

	// Create instance of m class
	void* construct(std::string const& m)
	{
		map_type::iterator i = m_classes.find(m);
		if (i == m_classes.end()) {
			throw std::invalid_argument("This is not a class");
		}
		return i->second();
	}
};
#endif