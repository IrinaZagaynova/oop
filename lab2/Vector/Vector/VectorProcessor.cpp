#include "VectorProcessor.h"
#include <algorithm>
using namespace std;

// Умножает каждый отрицательный элемент массива на произведение максимального и минимального элементов исходного массива
void ProcessVector(vector<double>& numbers)
{
	int numbersSize = numbers.size();
	if (numbersSize == 0)
	{
		return;
	}

	const auto result = std::minmax_element(numbers.begin(), numbers.end());

	auto MultiplyNegativeElementByMinAndMax = [result](double& number) {
		if (number < 0)
		{
			number = number * *result.first * *result.second;
		}
		return number;
	};

	std::transform(numbers.begin(), numbers.end(), numbers.begin(), MultiplyNegativeElementByMinAndMax);

}