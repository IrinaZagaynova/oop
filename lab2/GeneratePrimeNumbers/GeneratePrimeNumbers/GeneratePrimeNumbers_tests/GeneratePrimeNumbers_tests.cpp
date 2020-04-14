#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../GeneratePrimeNumbers/GeneratePrimeNumbers.h"

bool SetsAreEqual(const std::set<int>& x, const std::set<int>& y)
{
	return x == y;
}

TEST_CASE("Check if the argument is a digit within the bounds of the set")
{
	int upperBound;
	REQUIRE(IsItNumberWithinBoundsOfSet("", upperBound) == false);
	REQUIRE(IsItNumberWithinBoundsOfSet("A", upperBound) == false);
	REQUIRE(IsItNumberWithinBoundsOfSet("0", upperBound) == false);
	REQUIRE(IsItNumberWithinBoundsOfSet("-1", upperBound) == false);
	REQUIRE(IsItNumberWithinBoundsOfSet("100000001", upperBound) == false);
	REQUIRE(IsItNumberWithinBoundsOfSet("1", upperBound) == true);
	REQUIRE(upperBound == 1);
	REQUIRE(IsItNumberWithinBoundsOfSet("100000000", upperBound) == true);
	REQUIRE(upperBound == 100000000);
}

TEST_CASE("Check the generation of a set of prime numbers")
{
	REQUIRE(SetsAreEqual(GeneratePrimeNumbersSet(1), {}));
	REQUIRE(SetsAreEqual(GeneratePrimeNumbersSet(2), { 2 }));
	REQUIRE(SetsAreEqual(GeneratePrimeNumbersSet(7), { 2, 3, 5, 7 }));
	REQUIRE(SetsAreEqual(GeneratePrimeNumbersSet(30), { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 }));
}

TEST_CASE("Сheck the number of elements of the generated set")
{
	std::set<int> primeNumbers = GeneratePrimeNumbersSet(100000000);
	REQUIRE(primeNumbers.size() == 5761455);
}
