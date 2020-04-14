#include "GeneratePrimeNumbers.h"

int main(int argc, char* argv[])
{
	int upperBound;
	if (!ParseArgs(argc, argv, upperBound))
	{
		return 1;
	}

	std::set<int> primeNumbers = GeneratePrimeNumbersSet(upperBound);
	for (auto number : primeNumbers)
	{
		std::cout << number << " ";
	}

	return 0;
}


