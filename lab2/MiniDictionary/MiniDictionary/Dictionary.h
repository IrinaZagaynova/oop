#pragma once
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <fstream>

typedef std::map<std::string, std::string> Dictionary;

void FillInDictionaryFromFile(std::istream& streamInputDictionaryFile, Dictionary& dictionary);
bool TranslateLine(std::string line, std::string& translation, Dictionary dictionary);
bool AddLinesToDictionary(std::string line, std::string& translation, Dictionary& dictionary);
void SaveDictionaryToFile(const Dictionary& dictionary, std::ostream& dictionaryFile);