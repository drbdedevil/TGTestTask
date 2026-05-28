#include "String.h"

#include <cstring>
#include <utility>
#include <algorithm>

#include "iostream"

String::String(const char* str)
{
	if (!str)
		str = "";

	size = std::strlen(str);

	capacity = (size + 1) < MIN_CAPACITY ? MIN_CAPACITY : size + size / 2 + 1;

	data = new char[capacity];
	std::memcpy(data, str, size + 1);
}

String::String(const String& other) : size(other.size), capacity(other.capacity)
{
	data = new char[capacity];
	std::memcpy(data, other.data, other.size + 1);
}

String::String(String&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity)
{
	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;
}

String::~String() noexcept
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
}

const char* String::c_str() const noexcept
{
	return data ? data : "";
}

String& String::operator=(const String& other)
{
	if (&other == this)
		return *this;

	String tempString(other);
	swap(tempString);
	
	return *this;
}

String& String::operator=(String&& other) noexcept
{
	if (&other == this)
		return *this;

	delete[] data;

	data = other.data;
	size = other.size;
	capacity = other.capacity;

	other.data = nullptr;
	other.size = 0;
	other.capacity = 0;

	return *this;
}

String& String::operator+=(const char* other)
{
	if (!other || other[0] == '\0')
		return *this;

	const size_t other_size = std::strlen(other);
	const size_t required_size = size + other_size + 1;
	if (capacity < required_size)
	{
		capacity = required_size + required_size / 2 + 1;
		char* new_data = new char[capacity];

		std::memmove(new_data, data, size + 1);
		std::memmove(new_data + size, other, other_size + 1);

		delete[] data;
		data = new_data;
	}
	else
	{
		std::memmove(data + size, other, other_size + 1);
	}
	size += other_size;
	
	return *this;
}

String& String::operator+=(const String& other)
{
	return *this += other.c_str();
}

char& String::operator[](size_t index)
{
	return data[index];
}

const char& String::operator[](size_t index) const
{
	return data[index];
}

bool String::empty() const
{
	return size == 0;
}

size_t String::length() const
{
	return size;
}

size_t String::get_capacity() const
{
	return capacity;
}

void String::shrink_to_fit()
{
	if (capacity == size + 1)
		return;

	capacity = size + 1;
	char* new_data = new char[capacity];

	std::memcpy(new_data, data, size + 1);

	delete[] data;
	data = new_data;
}

void String::clear()
{
	size = 0;
	data[0] = '\0';
}

char& String::at(size_t index)
{
	if (index >= size)
		throw std::out_of_range("Index out of range!");

	return data[index];
}

const char& String::at(size_t index) const
{
	if (index >= size)
		throw std::out_of_range("Index out of range!");

	return data[index];
}

void String::swap(String& other) noexcept
{
	std::swap(data, other.data);
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
}