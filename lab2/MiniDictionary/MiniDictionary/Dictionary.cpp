#include "Dictionary.h"

bool AddLinesToDictionary(const std::string& line, std::string& lineTranslation, Dictionary& dictionary)
{
	if (lineTranslation != "")
	{
		dictionary.emplace(line, lineTranslation);
		return true;
	}
	return false;
}

bool TranslateLine(const std::string& line, std::string& lineTranslation, Dictionary dictionary)
{
	Dictionary::iterator it = dictionary.find(line);
	if (it != dictionary.end())
	{
		lineTranslation = it->second;
		return true;
	}

	return false;
}

