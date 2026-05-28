#pragma once

#include <iosfwd>
#include <utility>

class String
{
public:
	String();
	String(const char* str);
	String(const String& other);
	String(String&& other) noexcept;
	~String() noexcept;

	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;

	String& operator+=(const char* other);
	String& operator+=(const String& other);

	char& operator[](size_t index);
	const char& operator[](size_t index) const;

	bool empty() const;
	size_t length() const;
	size_t get_capacity() const;

	const char* c_str() const noexcept;

	void shrink_to_fit();
	void reserve(size_t new_capacity);
	void clear();

	char& at(size_t index);
	const char& at(size_t index) const;

	void swap(String& other) noexcept;

private:
	char* data;
	size_t size;
	size_t capacity;

	static constexpr size_t MIN_CAPACITY = 32;
};

inline void String::swap(String& other) noexcept
{
	std::swap(data, other.data);
	std::swap(size, other.size);
	std::swap(capacity, other.capacity);
}

inline std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os << str.c_str();
}

inline String operator+(const String& lhs, const String& rhs)
{
	return String(lhs) += rhs.c_str();
}

inline bool operator==(const String& lhs, const String& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) == 0;
}

inline bool operator!=(const String& lhs, const String& rhs)
{
	return !(lhs == rhs);
}

inline bool operator<(const String& lhs, const String& rhs)
{
	return std::strcmp(lhs.c_str(), rhs.c_str()) < 0;
}

inline bool operator>(const String& lhs, const String& rhs)
{
	return rhs < lhs;
}

inline bool operator<=(const String& lhs, const String& rhs)
{
	return !(rhs < lhs);
}

inline bool operator>=(const String& lhs, const String& rhs)
{
	return !(lhs < rhs);
}