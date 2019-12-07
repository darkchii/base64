#include "pch.h"
#include "base64/base64lib.h"
#include <iostream>

using namespace cli;

int main(int argc, char const*argv[])
{
	if (argc <= 1)
	{
		std::cout << "Usage: base64CLI [Options]\n";
		std::cout << "Options:\n";
		std::cout << "	[-e | --encode](Encoding for input text)\n";
		std::cout << "	[-d | --decode](Decoding for input text)\n";
		std::cout << "	[--thread](Threads)" << std::endl;
	}
	else
	{
		int i = 1;
		while (i <= argc)
		{
			if (!strcmp(argv[i], "-e") || !strcmp(argv[i], "--encode"))
			{
				++i;
				if (i + 1 < argc && !strcmp(argv[i + 1], "--thread"))
					std::cout << Base64::encode_or_decode(argv[i], E_ENCODE, true, std::size_t(argv[i + 2])) << std::endl;
				else
					std::cout << Base64::encode_or_decode(argv[i], E_ENCODE, false, 1) << std::endl;
			}
			else if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--decode"))
			{
				++i;
				if (!strcmp(argv[i + 1], "--thread"))
					std::cout << Base64::encode_or_decode(argv[i], E_DECODE, true, std::size_t(argv[i + 2])) << std::endl;
				else
					std::cout << Base64::encode_or_decode(argv[i], E_DECODE, false, 1) << std::endl;
			}
			i++;
		}
	}
	return 0;
}
