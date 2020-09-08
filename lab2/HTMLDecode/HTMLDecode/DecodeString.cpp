#include "DecodeString.h"
#include <iostream>
#include <vector>

const int MAX_LENGTH_OF_HTML_ENTITY = 6;
const int MIN_LENGTH_OF_HTML_ENTITY = 4;
const int NUMBER_PAIRS_OF_HTML_ENTITIES = 5;

struct PairOfEntities
{
	std::string decodedEntity;
	std::string entityToDecode;
};

const std::vector<PairOfEntities> htmlEntities = 
{
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" }
};

int FindPairOfEntitiesForDecoding(size_t position, const std::string& inputStr, int numberPairOfEntities)
{
	std::string str = "";
	for (size_t i = position; ((i < inputStr.length()) && (i < position + MAX_LENGTH_OF_HTML_ENTITY)); i++)
	{
		str += inputStr[i];	
		if (str.length() >= MIN_LENGTH_OF_HTML_ENTITY)
		{
			for (size_t j = 0; j < NUMBER_PAIRS_OF_HTML_ENTITIES; j++)
			{
				if (htmlEntities[j].decodedEntity == str)
				{
					numberPairOfEntities = j;
				}
			}
		}
	}
	return numberPairOfEntities;
}

std::string DecodeString(std::string const& inputStr)
{
	std::string decodedStr = "";
	size_t position = 0;
	int numberPairOfEntities = -1;

	while (position < inputStr.length())
	{
		numberPairOfEntities = -1;
		if (inputStr[position] == '&')
		{
			numberPairOfEntities = FindPairOfEntitiesForDecoding(position, inputStr, numberPairOfEntities);
		}
		if (numberPairOfEntities >= 0)
		{
			decodedStr += htmlEntities[numberPairOfEntities].entityToDecode;
			position += htmlEntities[numberPairOfEntities].decodedEntity.length();
		}
		else
		{
			decodedStr += inputStr[position];
			position++;
		}
	}

	return decodedStr;
}