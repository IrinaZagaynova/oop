#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorControl.h"

using namespace std;

int main()
{
	CCalculator calculator;
	CCalculatorControl CalculatorControl(calculator, cin, cout);

	while (!cin.eof() && !cin.fail())
	{
		cout << "> ";
		if (!CalculatorControl.HandleCommand())
		{
			cout << "Unknown command!" << endl;
		}
	}
	return 0;
}