#include "GeneratePrimeNumbers.h"

const int MAX_BOUND_OF_SET = 100000000;
const int MIN_BOUND_OF_SET = 1;

bool IsItNumberWithinBoundsOfSet(const std::string& str, int& upperBound)
{
	try
	{
		upperBound = std::stoi(str);
	}
	catch (const std::exception&)
	{
		return false;
	}

	if ((upperBound < MIN_BOUND_OF_SET) || (upperBound > MAX_BOUND_OF_SET))
	{
		return false;
	}

	return true;
}

bool ParseArgs(int argc, char* argv[], int& upperBound)
{
	if (argc != 2)
	{
		std::cout << "Invalid arguments count\n";
		std::cout << "Usage: GeneratePrimeNumbers.exe <upper bound number>\n";
		return false;
	}

	if (!IsItNumberWithinBoundsOfSet(argv[1], upperBound))
	{
		std::cout << "Invalid upper bound number\n";
		std::cout << "Use a number between 1 and 100000000\n";
		return false;
	}

	return true;
}

std::vector<bool> SelectPrimeNumbers(int upperBound)
{
	std::vector<bool> isPrimeNumber(upperBound + 1, true);
	for (size_t i = 2; i * i < isPrimeNumber.size(); i++)
	{
		if (isPrimeNumber[i])
		{
			for (size_t j = i * i; j < isPrimeNumber.size(); j += i)
			{
				isPrimeNumber[j] = false;
			}
		}
	}

	return isPrimeNumber;
}

std::set<int> GetPrimeNumbersSet(const std::vector<bool>& isPrimeNumber)
{
	std::set<int> primeNumbers;
	for (size_t i = 2; i < isPrimeNumber.size(); i++)
	{
		if (isPrimeNumber[i])
		{
			primeNumbers.emplace_hint(primeNumbers.end(), i);
		}
	}

	return primeNumbers;
}

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::vector<bool> isPrimeNumber = SelectPrimeNumbers(upperBound);
	std::set<int> primeNumbers = GetPrimeNumbersSet(isPrimeNumber);

	return primeNumbers;
}
