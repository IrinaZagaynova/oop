#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorHandler.h"

using namespace std;

int main()
{
	CCalculator calculator;
	CCalculatorHandler CalculatorHandler(calculator, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!CalculatorHandler.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	return 0;
}