#include <vector>
#include <iostream>
#include <algorithm>

#include "String.h"

int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Error: Need to pass arguments - " << argv[0] << " <string1> <string2> ..." << std::endl;
		return 1;
	}

	std::vector<String> argStrings;
	for (size_t i = 1; i < argc; ++i)
	{
		argStrings.push_back(String(argv[i]));
	}

	auto comparator = [](const String& lhs, const String& rhs)
		{
			const char* pLhs = lhs.c_str();
			const char* pRhs = rhs.c_str();

			while (*pLhs && *pRhs)
			{
				if (std::tolower(*pLhs) != std::tolower(*pRhs))
				{
					return std::tolower(*pLhs) > std::tolower(*pRhs);
				}
				++pLhs; ++pRhs;
			}

			return std::tolower(*pLhs) > std::tolower(*pRhs);
		};

	std::sort(argStrings.begin(), argStrings.end(), comparator);

	std::cout << "\nResult:" << std::endl;
	for (size_t i = 0; i < argStrings.size(); ++i)
	{
		std::cout << argStrings[i] << std::endl;
	}

	return 0;
}