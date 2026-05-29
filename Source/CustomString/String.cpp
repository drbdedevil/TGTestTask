#include "String.h"

#include <cstring>
#include <stdexcept>

namespace exstr
{

String::String() : String("") {}

String::String(const char* str)
{
    if (!str) str = "";

    size_ = std::strlen(str);

    if (size_ + 1 < MIN_CAPACITY)
        capacity_ = MIN_CAPACITY;
    else
        capacity_ = calculate_growth(size_);

    data_ = new char[capacity_];
    std::memcpy(data_, str, size_ + 1);
}

String::String(const String& other) : size_(other.size_), capacity_(other.capacity_)
{
    data_ = new char[capacity_];
    std::memcpy(data_, other.data_, other.size_ + 1);
}

String::String(String&& other) noexcept : data_(other.data_), size_(other.size_), capacity_(other.capacity_)
{
    other.data_ = new char[MIN_CAPACITY];
    other.data_[0] = '\0';
    other.size_ = 0;
    other.capacity_ = MIN_CAPACITY;
}

String::~String() noexcept
{
    delete[] data_;
}

String& String::operator=(const char* other)
{
    String temp(other);
    swap(temp);
    return *this;
}

String& String::operator=(const String& other)
{
    if (&other == this) return *this;

    String tempString(other);
    swap(tempString);

    return *this;
}

String& String::operator=(String&& other) noexcept
{
    if (&other == this) return *this;

    swap(other);

    return *this;
}

String& String::operator+=(const char* other)
{
    if (!other || other[0] == '\0') return *this;

    const size_t other_size = std::strlen(other);
    const size_t required_size = size_ + other_size + 1;
    if (capacity_ < required_size)
    {
        capacity_ = calculate_growth(required_size);
        char* new_data = new char[capacity_];

        std::memcpy(new_data, data_, size_);
        std::memcpy(new_data + size_, other, other_size + 1);

        delete[] data_;
        data_ = new_data;
    }
    else
    {
        // ƒолжно произойти перекрытие нуль-терминатора, поэтому используем более безопасный
        // в таком случае memmove вместо memcpy.
        std::memmove(data_ + size_, other, other_size + 1);
    }
    size_ += other_size;

    return *this;
}

String& String::operator+=(const String& other)
{
    return *this += other.c_str();
}

char& String::operator[](size_t index)
{
    return data_[index];
}

const char& String::operator[](size_t index) const
{
    return data_[index];
}

void String::reserve(size_t new_capacity)
{
    if (new_capacity <= capacity_) return;

    char* new_data = new char[new_capacity];
    std::memcpy(new_data, data_, size_ + 1);
    delete[] data_;

    data_ = new_data;
    capacity_ = new_capacity;
}

void String::resize(size_t new_size, char ch)
{
    if (size_ == new_size) return;

    if (new_size > size_)
    {
        if (new_size + 1 > capacity_)
        {
            reserve(new_size + 1);
        }
        std::memset(data_ + size_, ch, new_size - size_);
    }

    size_ = new_size;
    data_[size_] = '\0';
}

const char* String::c_str() const noexcept
{
    return data_;
}

bool String::empty() const noexcept
{
    return size_ == 0;
}

size_t String::length() const noexcept
{
    return size_;
}

size_t String::capacity() const noexcept
{
    return capacity_;
}

void String::shrink_to_fit()
{
    if (capacity_ == size_ + 1) return;

    capacity_ = size_ + 1;
    char* new_data = new char[capacity_];

    std::memcpy(new_data, data_, size_ + 1);

    delete[] data_;
    data_ = new_data;
}

void String::clear()
{
    size_ = 0;
    data_[0] = '\0';
}

void String::push_back(char ch)
{
    if (size_ + 1 > capacity_)
    {
        reserve(calculate_growth(size_ + 1));
    }

    data_[size_++] = ch;
    data_[size_] = '\0';
}

void String::pop_back()
{
    data_[--size_] = '\0';
}

char& String::at(size_t index)
{
    if (index >= size_) throw std::out_of_range("Index out of range!");

    return data_[index];
}

const char& String::at(size_t index) const
{
    if (index >= size_) throw std::out_of_range("Index out of range!");

    return data_[index];
}

void String::sort(bool (*ptrComparator)(char, char))
{
    if (size_ < 2) return;

    for (size_t i = 0; i < size_; ++i)
    {
        for (size_t j = size_ - 1; j > i; --j)
        {
            if (ptrComparator(data_[j], data_[j - 1]))
            {
                std::swap(data_[j], data_[j - 1]);
            }
        }
    }
}

size_t String::calculate_growth(size_t required) noexcept
{
    return required + required / GROW_COEFFICIENT + 1;
}

}  // namespace exstr