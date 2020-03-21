// Rle.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string> 
#include <optional>

using namespace std;

void RLECompression(istream& input, ostream& output)
{
	char character, previousCharacter;
	int identicalBytesNumber = 1;
	input.get(character);
	previousCharacter = character;
	if (input.eof())
	{
		return;
	}
	while (input.get(character))
	{
		if ((previousCharacter == character) && (identicalBytesNumber != 255))
		{
			identicalBytesNumber++;
		}
		else
		{
			output << static_cast<uint8_t>(identicalBytesNumber);
			output << static_cast<uint8_t>(previousCharacter);
			identicalBytesNumber = 1;
		}
		previousCharacter = character;
	}
	output << static_cast<uint8_t>(identicalBytesNumber);
	output << static_cast<uint8_t>(previousCharacter);
}

bool CheckFileSizeParity(istream& input)
{
	input.seekg(0, ios::end);
	int fileSize = (int)input.tellg();
	input.seekg(0, ios::beg);

	if (fileSize % 2 != 0)
	{
		cout << "Input file cannot be unpacked because it has an odd size\n";
		return false;
	}
	return true;
}

 void RLEDecompression(istream& input, ostream& output)
 {
	 char character;
	 uint8_t identicalBytesNumber;
	 while (input.get(character))
	 {
		 identicalBytesNumber = character;
		 input.get(character);
		 while (identicalBytesNumber > 0)
		 {	 
			 output << character;
			 identicalBytesNumber--;
		 }
	 }
 }

bool PackFile(const string& inputFileName, const string& outputFileName)
{
	ifstream input;
	input.open(inputFileName, ios_base::binary);
	if (!input.is_open())
	{
		cout << "Failed to open '" << inputFileName << "' for reading\n";
		return false;
	}

	ofstream output;
	output.open(outputFileName, ios_base::binary);
	if (!output.is_open())
	{
		cout << "Failed to open '" << outputFileName << "' for writing\n";
		return false;
	}

	RLECompression(input, output);

	if (input.bad())
	{
		cout << "Failed to read data from input file\n";
		return false;
	}

	if (!output.flush())
	{
		cout << "Failed to write data to output file\n";
		return false;
	}

	return true;
}

bool UnpackFile(const string& inputFileName, const string& outputFileName)
{
	ifstream input;
	input.open(inputFileName, ios_base::binary);
	if (!input.is_open())
	{
		cout << "Failed to open '" << inputFileName << "' for reading\n";
		return false;
	}

	ofstream output;
	output.open(outputFileName, ios_base::binary);
	if (!output.is_open())
	{
		cout << "Failed to open '" << outputFileName << "' for writing\n";
		return false;
	}

	if (!CheckFileSizeParity(input))
	{
		return false;
	}
	RLEDecompression(input, output);

	if (input.bad())
	{
		cout << "Failed to read data from input file\n";
		return false;
	}

	if (!output.flush())
	{
		cout << "Failed to write data to output file\n";
		return false;
	}

	return true;
}

enum class Mode
{
	pack, unpack
};

bool DefineMode(const string& firstArg, Mode& mode)
{
	if (firstArg == "pack")
	{
		mode = Mode::pack;
	}
	else if (firstArg == "unpack")
	{
		mode = Mode::unpack;
	}
	else
	{
		cout << "The first command line parameter should be <pack> or <unpack>\n";
		return false;
	}
	return true;
}

struct Args
{ 
	string inputFileName;
	string outputFileName;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: compare.exe <action> <input file> <output file>\n";
		return nullopt;
	}
	Args args;
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];

	return args;
}

int main(int argc, char* argv[])
{
    auto args = ParseArgs(argc, argv);

	if (!args)
	{
		return 1;
	}

	Mode mode;
	string firstArg = argv[1];
	if (!DefineMode(firstArg, mode))
	{
		return 1;
	}
	if (mode == Mode::pack)
	{
		if (!PackFile(args->inputFileName, args->outputFileName))
		{
			return 1;
		}
	}
	else if (mode == Mode::unpack)
	{
		if (!UnpackFile(args->inputFileName, args->outputFileName))
		{
			return 1;
		}
	}

	return 0;
}

