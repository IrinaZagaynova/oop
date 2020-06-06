#pragma once
#include <stdexcept>

class CUrlParsingError : public std::invalid_argument
{
public:
	explicit CUrlParsingError(const char* message) 
		:std::invalid_argument(message) 
	{
	}
};
