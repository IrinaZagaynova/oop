// Rle.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string> 
#include <optional>
#include <functional>

using namespace std;

using StreamProcessor = function<bool(istream& input, ostream& output)>;

struct RLEChunk
{
	char ch;
	uint8_t counter = 0;
};

bool FlushChunk(RLEChunk& chunk, ostream& output)
{
	if (!output.put(chunk.counter))
	{
		return false; 
	}
	if (!output.put(static_cast<uint8_t>(chunk.ch)))
	{
		return false;
	}
	return true;
}

bool CompressChar(char ch, RLEChunk& chunk, ostream& output)
{
	if (chunk.counter == 0)
	{
		chunk.ch = ch;
	}
	if ((chunk.ch == ch) && (chunk.counter < 255))
	{
		chunk.counter++;
	}
	else
	{
		if (!FlushChunk(chunk, output))
		{
			return false;
		}
		chunk.counter = 0;
	}
	return true;
}

bool RLECompression(istream& input, ostream& output)
{
	char ch;
	RLEChunk chunk;
	while (input.get(ch))
	{
		if (!CompressChar(ch, chunk, output))
		{
			return false;
		}
	}
	if (chunk.counter != 0)
	{
		FlushChunk(chunk, output);
	}
	return true;
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

 bool RLEDecompression(istream& input, ostream& output)
 {
	 if (!CheckFileSizeParity(input))
	 {
		 return false;
	 }
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
	 return true;
 }

bool ProcessFiles(string const& inputFileName, string const& outputFileName, StreamProcessor processStreams)
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

	if (!processStreams(input, output))
	{
		return false;
	}

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

struct Args
{
	string inputFileName;
	string outputFileName;
	Mode mode;
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
	string firstArg = argv[1];
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];

	if (firstArg == "pack")
	{
		args.mode = Mode::pack;
	}
	else if (firstArg == "unpack")
	{
		args.mode = Mode::unpack;
	}
	else
	{
		return nullopt;
	}

	return args;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	if (args->mode == Mode::pack)
	{
		if (!ProcessFiles(args->inputFileName, args->outputFileName, RLECompression))
		{
			return 1;
		}
	}
	else
	{
		if (!ProcessFiles(args->inputFileName, args->outputFileName, RLEDecompression))
		{
			return 1;
		}
	}

	return 0;
}

