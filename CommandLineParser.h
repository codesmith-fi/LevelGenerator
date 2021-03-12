#ifndef _GENERATOR_COMMANDLINEPARSER_H_DEFINED
#define _GENERATOR_COMMANDLINEPARSER_H_DEFINED

#include <string>
#include <vector>

namespace Generator
{
	class CommandLineParser
	{
	public:
		static const std::string parseString(const std::string& token, int c, char** p);
		static const int parseInt(const std::string& token, int c, char** p);
	};
}
#endif
