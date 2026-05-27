#include <iostream>

#include "String.h"

int main()
{
	String exampleString("Hello, world!");
	String exampleString1 = "Some string";
	exampleString = std::move(exampleString1);

	std::cout << exampleString << std::endl;

	const char* ch = exampleString.c_str();
	while (*ch != '\0')
	{
		ch = ch + 1;
		std::cout << *ch << std::endl;
	}

	exampleString1.reserve(200);

	return 0;
}