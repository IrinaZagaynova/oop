// MiniDictionary.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "Dictionary.h"
#include <cstdlib>
#include <windows.h>

bool ConfirmSavingDictionaryToFile(const Dictionary& dictionary, const std::string& dictionaryFileName)
{
	std::cout << "В словарь были внесены изменения. Введите Y или y для сохранения перед выходом.\n";
	std::string line;
	getline(std::cin, line);
	if ((line == "Y") || (line == "y"))
	{
		std::ofstream dictionaryFile(dictionaryFileName);
		std::ostream& streamOutputDictionaryFile = dictionaryFile;
		SaveDictionaryToFile(dictionary, streamOutputDictionaryFile);
		std::cout << "Изменения сохранены. До свидания.\n";
	}
	else
	{
		std::cout << "Изменения не сохранены. До свидания.\n";
	}

	return true;
}

void ProcessUnknownLine(const std::string& line, Dictionary& dictionary, bool& dictionaryChanges)
{
	std::string translation;
	std::cout << "Неизвестное слово \"" << line << "\". Введите перевод или пустую строку для отказа." << "\n";
	getline(std::cin, translation);
	if (AddLinesToDictionary(line, translation, dictionary))
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
	std::string translation;
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
		else if (TranslateLine(line, translation, dictionary))
		{
			std::cout << translation << "\n";
		}
		else
		{
			ProcessUnknownLine(line, dictionary, dictionaryChanges);
		}
	}
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
		std::ifstream dictionaryFile(dictionaryFileName);
		if (!dictionaryFile.is_open())
		{
			return 1;
		}
		std::istream& streamInputDictionaryFile = dictionaryFile;
		FillInDictionaryFromFile(streamInputDictionaryFile, dictionary);
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
