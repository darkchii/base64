#include "pch.h"
#include "base64/base64lib.h"
#include <iostream>

using namespace cli;

int main(int argc, char**argv)
{
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
				if (!strcmp(argv[++i], "--thread"))
					std::cout << Base64::encode(argv[i - 1], true, std::size_t(argv[++i])) << std::endl;
				else
					std::cout << Base64::encode(argv[i - 1], false, 1) << std::endl;
			}
			else if (!strcmp(argv[i], "-d") || !strcmp(argv[i], "--decode"))
			{
				++i;
				if (!strcmp(argv[++i], "--thread"))
					std::cout << Base64::decode(argv[i - 1], true, std::size_t(argv[++i])) << std::endl;
				else
					std::cout << Base64::decode(argv[i - 1], false, 1) << std::endl;
			}
			i++;
		}
	}
	return 0;
}
