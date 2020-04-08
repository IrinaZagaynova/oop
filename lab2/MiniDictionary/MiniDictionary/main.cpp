// MiniDictionary.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Dictionary.h"
#include <fstream>
#include <cstdlib>
#include <windows.h>

bool SaveDictionaryToFile(const Dictionary& dictionary, const std::string& dictionaryFileName)
{
	std::ofstream dictionaryFile(dictionaryFileName);
	for (auto& line : dictionary)
	{
		dictionaryFile << line.first << "\n" << line.second << "\n";
	}

	if (!dictionaryFile.flush())
	{
		return false;
	}

	return true;
}

bool ConfirmSavingDictionaryToFile(const Dictionary& dictionary, const std::string& dictionaryFileName)
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
	std::string line;
	getline(std::cin, line);
	if ((line == "Y") || (line == "y"))
	{
		if (SaveDictionaryToFile(dictionary, dictionaryFileName))
		{
			std::cout << "Изменения сохранены. До свидания.\n";
		}
		else
		{
			std::cout << "Не удалось записать данные в файл словаря\n";
			return false;
		}
	}
	else
	{
		std::cout << "Изменения не сохранены. До свидания.\n";
	}

	return true;
}

void ProcessUnknownWord(const std::string& line, Dictionary& dictionary, bool& dictionaryChanges)
{
	std::string lineTranslation;
	std::cout << "Неизвестное слово \"" << line << "\". Введите перевод или пустую строку для отказа." << "\n";
	getline(std::cin, lineTranslation);
	if (AddLinesToDictionary(line, lineTranslation, dictionary))
	{
		dictionaryChanges = true;
	}
	else
	{
		std::cout << "Слово \"" << line << "\" проигнорировано." << "\n";
	}
}

void ProcessInputLines(Dictionary dictionary, const std::string& dictionaryFileName)
{
	std::string line;
	std::string lineTranslation;
	bool dictionaryChanges = false;
	while (getline(std::cin, line))
	{
		if (line == "...")
		{
			if (dictionaryChanges)
			{
				ConfirmSavingDictionaryToFile(dictionary, dictionaryFileName);
			}
			return;
		}
		else if (TranslateLine(line, lineTranslation, dictionary))
		{
			std::cout << lineTranslation << "\n";
		}
		else
		{
			ProcessUnknownWord(line, dictionary, dictionaryChanges);
		}
	}
}

bool FillInDictionaryFromFile(const std::string& dictionaryFileName, Dictionary& dictionary)
{
	std::ifstream dictionaryFile(dictionaryFileName);
	if (!dictionaryFile.is_open())
	{
		return false;
	}

	std::string firstStr;
	std::string secondStr;
	while (getline(dictionaryFile, firstStr) && getline(dictionaryFile, secondStr))
	{
		dictionary.emplace(firstStr, secondStr);
	}

	return true;
}

int main(int argc, char* argv[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Dictionary dictionary;
	std::string dictionaryFileName;
	if (argc == 2)
	{
		dictionaryFileName = argv[1];
		if (!FillInDictionaryFromFile(dictionaryFileName, dictionary))
		{
			std::cout << "Error filling dictionary from file\n";
			return 1;
		}
	}
	else
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: MiniDictionary.exe <dictionary file name>\n";
		return 1;
	}

	ProcessInputLines(dictionary, dictionaryFileName);

	return 0;
}
