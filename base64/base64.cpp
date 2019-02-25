// base64.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "base64lib.h"
#include <iostream>

int main(int argc, char**argv)
{
	Base64 base64;

	if (argc <= 1)
    {
		std::cout << "Usage:" << std::endl;
		std::cout << "	[-e | --encode] [text](encoding for input text)" << std::endl;
		std::cout << "	[-d | --decode] [text](decoding for input text)" << std::endl;
		std::cout << "	[--thread] [threads](open thread)" << std::endl;
    }
	else
	{
		int i = 1;
		while (i <= argc)
		{
			if (!strcmp(argv[i], "-e") || !strcmp(argv[i], "--encode"))
			{
				++i;
				if (!strcmp(argv[i], "--thread"))
					std::cout << base64.encode(argv[i - 1], true, std::size_t(argv[++i])) << std::endl;
				else
					std::cout << base64.encode(argv[i - 1], false, 1) << std::endl;
			}
			else if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--decode"))
			{
				++i;
				if (!strcmp(argv[i], "--thread"))
					std::cout << base64.decode(argv[i - 1], true, std::size_t(argv[++i])) << std::endl;
				else
					std::cout << base64.decode(argv[i - 1], false, 1) << std::endl;
			}
			i++;
		}
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
