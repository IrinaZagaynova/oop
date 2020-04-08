#pragma once
#include <iostream>
#include <string>
#include <map>

typedef std::map<std::string, std::string> Dictionary;

bool TranslateLine(const std::string& line, std::string& lineTranslation, Dictionary dictionary);
bool AddLinesToDictionary(const std::string& line, std::string& lineTranslation, Dictionary& dictionary);