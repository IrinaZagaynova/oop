#include "DecodeString.h"
#include <iostream>
#include <vector>

struct PairOfEntities
{
	std::string decodedEntity;
	std::string entityToReplace;
};

std::vector<PairOfEntities> htmlEntities = 
{
	{ "&quot;", "\"" },
	{ "&apos;", "'" },
	{ "&lt;", "<" },
	{ "&gt;", ">" },
	{ "&amp;", "&" }
};

std::string ReplaceEntitiesInString(const std::string& decodingStr, const std::string& decodedEntity, const std::string& entityToReplace)
{
	std::string resultStr = decodingStr;

	size_t position = resultStr.find(decodedEntity);
	while (position != std::string::npos)
	{
		resultStr.replace(position, decodedEntity.size(), entityToReplace);
		position = resultStr.find(decodedEntity, position);
	}

	return resultStr;
}

std::string DecodeString(std::string const& inputStr)
{
	std::string decodingStr = inputStr;

	for (PairOfEntities entity : htmlEntities)
	{
		decodingStr = ReplaceEntitiesInString(decodingStr, entity.decodedEntity, entity.entityToReplace);
	}

	return decodingStr;
}