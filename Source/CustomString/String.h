#pragma once

#include <iosfwd>

class String
{
public:
	String(const char* str = "");
	~String();

	void reserve(size_t new_capacity);

	const char* c_str() const;

private:
	char* data;
	size_t size;
	size_t capacity;

	static constexpr size_t MIN_CAPACITY = 32;

	// TODO: удалить
	void printCapacity();
};

inline std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os << str.c_str();
}