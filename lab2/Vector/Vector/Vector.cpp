#include <iostream>
#include <iterator>
#include <iomanip>
#include "VectorProcessor.h"

using namespace std;

int main()
{
	vector<double> numbers(istream_iterator<double>(cin), (istream_iterator<double>()));
	ProcessVector(numbers);
	cout << fixed << setprecision(3);
	copy(numbers.begin(), numbers.end(), ostream_iterator<double>(cout, " "));
	return 0;
}