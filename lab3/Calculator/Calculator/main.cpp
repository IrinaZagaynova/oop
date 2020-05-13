#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorControl.h"

using namespace std;

int main()
{
	CCalculator calculator;
	CCalculatorControl calculatorControl(calculator, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!calculatorControl.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	return 0;
}