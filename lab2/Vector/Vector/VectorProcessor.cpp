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
	double minElenentValue = *min_element(numbers.begin(), numbers.end());
	double maxElenentValue = *max_element(numbers.begin(), numbers.end());
	for (int i = 0; i < numbersSize; i++)
	{
		if (numbers[i] < 0)
		{
			numbers[i] = numbers[i] * minElenentValue * maxElenentValue;
		}
	}
}