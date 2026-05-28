#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../CustomString/String.h"

#include <cstring>

// ========== Тесты конструкторов ==========
TEST_CASE("String default constructor") 
{
    String s;

    CHECK(s.c_str() != nullptr);
    CHECK(s.length() == 0);
    CHECK(std::strcmp(s.c_str(), "") == 0);
}

TEST_CASE("String constructor from C-string") 
{
    String s("Hello, Targem!");

    CHECK(s.length() == 14);
    CHECK(std::strcmp(s.c_str(), "Hello, Targem!") == 0);
}

TEST_CASE("String constructor from empty C-string") 
{
    String s("");

    CHECK(s.length() == 0);
    CHECK(std::strcmp(s.c_str(), "") == 0);
}

// ========== Тесты копирования ==========
TEST_CASE("String copy constructor") 
{
    String original("Copy me");
    String copy(original);

    CHECK(copy.length() == original.length());
    CHECK(std::strcmp(copy.c_str(), original.c_str()) == 0);

    // Изменение копии не влияет на оригинал
    copy += "!";
    CHECK(std::strcmp(original.c_str(), "Copy me") == 0);
    CHECK(std::strcmp(copy.c_str(), "Copy me!") == 0);
}

// ========== Тесты перемещения ==========
TEST_CASE("String move constructor") 
{
    String source("Move me");
    const char* source_ptr = source.c_str();

    String destination(std::move(source));

    CHECK(destination.length() == 7);
    CHECK(std::strcmp(destination.c_str(), "Move me") == 0);

    // source теперь пустой, но валидный
    CHECK(source.length() == 0);
    CHECK(std::strcmp(source.c_str(), "") == 0);
}

// ========== Тесты операторов ==========
TEST_CASE("String assignment operator") 
{
    String a("First");
    String b("Second");

    a = b;

    CHECK(a.length() == b.length());
    CHECK(std::strcmp(a.c_str(), b.c_str()) == 0);
}

TEST_CASE("String self-assignment") 
{
    String s("Hello");
    s = s;

    CHECK(std::strcmp(s.c_str(), "Hello") == 0);
}

TEST_CASE("String move assignment") 
{
    String a("First");
    String b("Second");

    a = std::move(b);

    CHECK(std::strcmp(a.c_str(), "Second") == 0);
    CHECK(b.length() == 0);
}

// ========== Тесты конкатенации ==========
TEST_CASE("String concatenation with C-string") 
{
    String s("I want to work at ");
    s += "Targem Games!";

    CHECK(std::strcmp(s.c_str(), "I want to work at Targem Games!") == 0);
}

TEST_CASE("String concatenation with String") 
{
    String s1("I want to work at ");
    String s2("Targem Games!");
    s1 += s2;

    CHECK(std::strcmp(s1.c_str(), "I want to work at Targem Games!") == 0);
}

TEST_CASE("String concatenation with self") 
{
    String s("VeryMuch");
    s += s.c_str(); 

    CHECK(std::strcmp(s.c_str(), "VeryMuchVeryMuch") == 0);
}

// ========== Тесты сравнения ==========
TEST_CASE("String equality") 
{
    CHECK(String("Hello") == String("Hello"));
    CHECK_FALSE(String("Hello") == String("World"));
    CHECK(String("Hello") != String("World"));
    CHECK(String("") == String(""));
}

TEST_CASE("String comparison operators") 
{
    CHECK(String("Rockstar") < String("Targem"));
    CHECK(String("Targem") > String("Rockstar"));
    CHECK(String("Targem") <= String("Targem"));
    CHECK(String("Targem") >= String("Targem"));
}

// ========== Тесты работы с C-строками ==========
TEST_CASE("String c_str returns null-terminated string") 
{
    String s("Test");

    const char* ptr = s.c_str();

    for (size_t i = 0; i < s.length(); ++i)
        CHECK(ptr[i] != '\0');
    
    CHECK(ptr[s.length()] == '\0');
}

// ========== Тесты с SUBCASE ==========
TEST_CASE("String reserve and capacity") 
{
    String s("Hello");

    SUBCASE("reserve increases capacity") 
    {
        size_t old_capacity = s.get_capacity();
        s.reserve(old_capacity + 100);
        CHECK(s.get_capacity() >= old_capacity + 100);
        CHECK(std::strcmp(s.c_str(), "Hello") == 0);
    }

    SUBCASE("reserve smaller does nothing") 
    {
        size_t old_capacity = s.get_capacity();
        s.reserve(old_capacity - 10);
        CHECK(s.get_capacity() == old_capacity);
    }
}

// ========== Тесты вспомогательных методов ==========
TEST_CASE("Clear String")
{
    String s("Don't delete me!");
    s.clear();

    CHECK(s.c_str() != nullptr);
    CHECK(s.length() == 0);
    CHECK(std::strcmp(s.c_str(), "") == 0);
}

TEST_CASE("String operator[] non-const access")
{
    String s("Hello");

    CHECK(s[0] == 'H');
    CHECK(s[4] == 'o');

    s[0] = 'J';
    CHECK(s[0] == 'J');
    CHECK(std::strcmp(s.c_str(), "Jello") == 0);

    s[4] = '!';
    CHECK(s[4] == '!');
    CHECK(std::strcmp(s.c_str(), "Jell!") == 0);

    const String s1("Hello");

    CHECK(s1[0] == 'H');
    CHECK(s1[4] == 'o');
}

TEST_CASE("String at() non-const access")
{
    String s("Hello");

    CHECK(s.at(0) == 'H');
    CHECK(s.at(4) == 'o');

    s.at(0) = 'J';
    CHECK(s.at(0) == 'J');
    CHECK(std::strcmp(s.c_str(), "Jello") == 0);

    const String s1("Hello");

    CHECK(s1.at(0) == 'H');
    CHECK(s1.at(4) == 'o');
}

TEST_CASE("String at() throws on invalid index")
{
    String s("Hello");

    CHECK_THROWS_AS(s.at(5), std::out_of_range);
    CHECK_THROWS_AS(s.at(100), std::out_of_range);
    CHECK_THROWS_AS(s.at(9999), std::out_of_range);

    CHECK_NOTHROW(s.at(0));
    CHECK_NOTHROW(s.at(4));

    String empty;
    CHECK_THROWS_AS(empty.at(0), std::out_of_range);
}

TEST_CASE("String at() works after clear")
{
    String s("Hello");
    s.clear();

    CHECK(s.length() == 0);
    CHECK_THROWS_AS(s.at(0), std::out_of_range);
}

TEST_CASE("String at() works after move")
{
    String source("Hello");
    String destination(std::move(source));

    CHECK(destination.at(0) == 'H');
    CHECK(destination.at(4) == 'o');

    CHECK_THROWS_AS(source.at(0), std::out_of_range);
}