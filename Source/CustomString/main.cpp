#include <vector>
#include <iostream>
#include <algorithm>

#include "String.h"

bool charLess(char l, char r)
{
    return l < r;
}

bool charMore(char l, char r)
{
    return l > r;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Error: Need to pass arguments - " << argv[0] << " <string1> <string2> ..." << std::endl;
        return 1;
    }

    std::vector<exstr::String> argStrings;
    for (size_t i = 1; i < argc; ++i)
    {
        exstr::String str(argv[i]);
        // str.sort(&charMore); // - вдруг захочется отсортировать саму строку :D
        argStrings.push_back(str);
    }

    auto comparator = [](const exstr::String& lhs, const exstr::String& rhs)
    {
        for (size_t i = 0; i < std::min(lhs.length(), rhs.length()); ++i)
        {
            char left = static_cast<char>(std::tolower(lhs[i]));
            char right = static_cast<char>(std::tolower(rhs[i]));

            if (left > right)
                return true;
            else if (right > left)
                return false;
        }
        return lhs.length() > rhs.length();
    };

    std::sort(argStrings.begin(), argStrings.end(), comparator);

    std::cout << "\nResult:" << std::endl;
    for (size_t i = 0; i < argStrings.size(); ++i)
    {
        std::cout << argStrings[i] << std::endl;
    }

    return 0;
}