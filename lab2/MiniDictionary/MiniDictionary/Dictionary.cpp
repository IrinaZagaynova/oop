#include "Dictionary.h"

void FillInDictionaryFromFile(std::istream& dictionaryFile, Dictionary& dictionary)
{
	std::string line;
	std::string translation;
	while (getline(dictionaryFile, line) && getline(dictionaryFile, translation))
	{
		transform(line.begin(), line.end(), line.begin(), tolower);
		dictionary.emplace(line, translation);
	}
}

bool AddLinesToDictionary(std::string line, std::string& translation, Dictionary& dictionary)
{
	if (translation != "")
	{
		transform(line.begin(), line.end(), line.begin(), tolower);
		dictionary.emplace(line, translation);
		return true;
	}
	return false;
}

bool TranslateLine(std::string line, std::string& translation, Dictionary dictionary)
{
	transform(line.begin(), line.end(), line.begin(), tolower);
	Dictionary::iterator it = dictionary.find(line);
	if (it != dictionary.end())
	{
		translation = it->second;
		return true;
	}

	return false;
}

void SaveDictionaryToFile(const Dictionary& dictionary, std::ostream& dictionaryFile)
{
	for (auto& line : dictionary)
	{
		dictionaryFile << line.first << "\n" << line.second << "\n";
	}
}