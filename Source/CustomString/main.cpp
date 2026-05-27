#include <iostream>

#include "String.h"

int main()
{
	String exampleString("Hello, world!");

	std::cout << exampleString << std::endl;

	const char* ch = exampleString.c_str();
	while (*ch != '\0')
	{
		ch = ch + 1;
		std::cout << *ch << std::endl;
	}

	exampleString.reserve(200);

	return 0;
}