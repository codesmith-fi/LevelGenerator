#include "CommandLineParser.h"
#include <iostream>
#include <stdlib.h>

namespace Generator
{
	const std::string CommandLineParser::parseString(const std::string& token, int c, char** p)
	{
		std::string res;
		for (int i = 0; i < c; ++i)
		{
			std::string current(p[i]);
			if (current.compare(token) && i < c - 2) {
				res = current;
			}
		}
		return res;
	}

	const int CommandLineParser::parseInt(const std::string& token, int c, char** p)
	{
		int res=0;
		for (int i = 0; i < c; ++i)
		{
			std::string current(p[i]);
			if (current.compare(token) == 0 && i<c-1) {
				res = atoi(p[i+1]);
			}
		}
		return res;
	}
}
