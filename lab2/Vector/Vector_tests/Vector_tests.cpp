#include <iostream>
#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "../Vector/VectorProcessor.h"

using namespace std;

bool VectorsAreEqual(vector<double> const& x, vector<double> const& y)
{
	return x == y;
}

TEST_CASE("Make empty vector from empty vector")
{
	// Создает пустой вектор из пустого вектора
	vector<double> emptyVector;
	ProcessVector(emptyVector);
	REQUIRE(emptyVector.empty());
}

TEST_CASE("Make a vector, each negative element of which is multiplied by the product of the maximum and minimum elements of the original vector")
{
	// Не изменит содержимое вектора, который не содержит отрицательных чисел
	vector<double> numbers = { 4, 1, 0, 3 };
	auto copy(numbers); 
	ProcessVector(numbers);
	REQUIRE(numbers == copy);

	// Умножит отрицательные числа на максимальный и минимальный элемент исходного массива
	numbers = { 4, -1, 0, -3 };
	ProcessVector(numbers);
	REQUIRE(VectorsAreEqual(numbers,
		{ 4, (-1 * 4 * -3), 0, (-3 * 4 * -3)}
	));

}
