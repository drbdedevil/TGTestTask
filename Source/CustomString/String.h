#pragma once

#include <iosfwd>

class String
{
public:
	String(const char* str = "");
	String(const String& other);
	String(String&& other) noexcept;
	~String() noexcept;

	void reserve(size_t new_capacity);

	const char* c_str() const noexcept;

	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;

	void swap(String& other) noexcept;
private:
	char* data;
	size_t size;
	size_t capacity;

	static constexpr size_t MIN_CAPACITY = 32;

	// TODO: удалить
	void printInfo();
};

inline std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os << str.c_str();
}