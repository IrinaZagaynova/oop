// FlipByte.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string> 

using namespace std;

unsigned char FlipByte(unsigned char& inputByte)
{
	unsigned char flipNumber = 0;
	for (int i = 0; i < 8; ++i)
	{
		flipNumber <<= 1;
		flipNumber |= inputByte & 1;
		inputByte >>= 1;
	}
	return flipNumber;
}

bool ParseArgs(int argc, char* argv[], unsigned char& inputByte)
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: flipbyte.exe <input number>\n";
		return false;
	}

	int parsedNumber;
	try
	{
		parsedNumber = stoi(argv[1]);
	}
	catch (const invalid_argument & err)
	{
		cout << err.what() << "\n";
		return false;
	}
	catch (const out_of_range & err)
	{
		cout << err.what() << "\n";
		return false;
	}

	if ((parsedNumber < 0) || (parsedNumber > 255))
	{
		cout << "invalid argument\n";
		return false;
	}

	inputByte = static_cast<unsigned char>(parsedNumber);
	return true;
}

int main(int argc, char* argv[])
{
	unsigned char inputByte;

	if (!ParseArgs(argc, argv, inputByte))
	{
		cout << "input must be a decimal number in the byte range\n";
		return 1;
	}

	cout << static_cast<int>(FlipByte(inputByte)) << "\n";

	return 0;
}