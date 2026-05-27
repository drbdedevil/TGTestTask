#include "String.h"

#include <cstring>
#include <algorithm>

// TODO: удалить
#include <iostream>

String::String(const char* str)
{
	size = std::strlen(str);

	capacity = (size + 1) < MIN_CAPACITY ? MIN_CAPACITY : static_cast<size_t>(size * 1.5) + 1;

	data = new char[capacity];
	std::memcpy(data, str, size + 1);

	// TODO: удалить
	printCapacity();
}

String::~String()
{
	delete[] data;
}

void String::reserve(size_t new_capacity)
{
	if (new_capacity <= capacity)
		return;

	char* new_data = new char[new_capacity];
	std::memcpy(new_data, data, size + 1);
	delete[] data;

	data = new_data;
	capacity = new_capacity;

	// TODO: удалить
	printCapacity();
}

const char* String::c_str() const
{
	return data;
}

void String::printCapacity()
{
	std::cout << "Capacity = " << capacity << std::endl;
}