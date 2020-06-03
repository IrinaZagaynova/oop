#include "stdafx.h"
#include "../Calculator/CalculatorHandler.h"
#include "../Calculator/Calculator.h"
#include <sstream>
#include <boost/optional.hpp>

using namespace std;
using boost::optional;
using boost::none;

struct CalculatorControlDependencies
{
	CCalculator calculator;
	stringstream input;
	stringstream output;
};

struct CalculatorControlFixture : CalculatorControlDependencies
{
	CCalculatorHandler CalculatorHandler;

	CalculatorControlFixture()
		: CalculatorHandler(calculator, input, output)
	{
	}

	void VerifyCommandHandling(const string& command, const string& expectedOutput)
	{
		output = stringstream();
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(CalculatorHandler.HandleCommand());
		BOOST_CHECK(input.eof());
		BOOST_CHECK_EQUAL(output.str(), expectedOutput);
	}

	void ExecuteCommand(const string& command)
	{
		input = stringstream();
		BOOST_CHECK(input << command);
		BOOST_CHECK(CalculatorHandler.HandleCommand());
		BOOST_CHECK(input.eof());
	}
};

BOOST_FIXTURE_TEST_SUITE(Remote_Control, CalculatorControlFixture)

BOOST_AUTO_TEST_CASE(can_declare_variable_with_correct_undeclared_name)
{
	ExecuteCommand("var identifier_123");
	BOOST_CHECK(calculator.DoesVariablesExist("identifier_123"));
}

BOOST_AUTO_TEST_CASE(cant_declare_variable_if_its_already_declared)
{
	calculator.DeclareVariable("identifier");
	VerifyCommandHandling("var identifier", "Failed to declare a variable\n");
}

BOOST_AUTO_TEST_CASE(cant_declare_variable_with_incorrect_name)
{
	VerifyCommandHandling("var 1identifier", "Failed to declare a variable\n");
	VerifyCommandHandling("var vari able", "Failed to declare a variable\n");
	VerifyCommandHandling("var 5 10", "Failed to declare a variable\n");
}

BOOST_AUTO_TEST_CASE(cant_declare_variable_if_command_is_entered_incorrectly)
{
	VerifyCommandHandling("var", "Failed to declare a variable\n");
	VerifyCommandHandling("var  ", "Failed to declare a variable\n");
}

BOOST_AUTO_TEST_CASE(can_assign_variable_value_of_variable_or_function)
{
	calculator.AssignValueToVariable("x", 10);
	ExecuteCommand("let varX=x");
	BOOST_CHECK_EQUAL(calculator.GetValueOfVariable("x"), 10);

	calculator.AssignValueToVariable("y", 20);
	calculator.DeclareFunction("fnY", "y");
	ExecuteCommand("let varY=fnY");
	BOOST_CHECK_EQUAL(calculator.GetValueOfVariable("varY"), 20);
}

BOOST_AUTO_TEST_CASE(cant_assign_variable_value_of_undeclared_identifier)
{
	VerifyCommandHandling("let name=undeclared_identifier", "Failed to assign value to variable\n");
}

BOOST_AUTO_TEST_CASE(cant_assign_value_to_variable_with_incorrect_name)
{
	calculator.AssignValueToVariable("x", 10);
	VerifyCommandHandling("let 1name=x", "Failed to assign value to variable\n");
	VerifyCommandHandling("let na me=x", "Failed to assign value to variable\n");
	VerifyCommandHandling("let имя=x", "Failed to assign value to variable\n");
}

BOOST_AUTO_TEST_CASE(cant_assign_value_to_variable_if_command_is_entered_incorrectly)
{
	VerifyCommandHandling("let", "Failed to assign value to variable\n");
	VerifyCommandHandling("let x", "Failed to assign value to variable\n");
}

BOOST_AUTO_TEST_CASE(cant_assign_value_to_variable_if_its_already_declared)
{
	calculator.DeclareVariable("identifier");
	VerifyCommandHandling("let identifier=x", "Failed to assign value to variable\n");
}

BOOST_AUTO_TEST_CASE(can_declare_function_with_correct_undeclared_name)
{
	calculator.AssignValueToVariable("x", 10);
	ExecuteCommand("fn fnX=x");
	BOOST_CHECK(calculator.DoesFunctionExist("fnX"));
	BOOST_CHECK_EQUAL(calculator.GetValueOfFunction("fnX"), 10);

	ExecuteCommand("fn XPlusX=x+x");
	BOOST_CHECK(calculator.DoesFunctionExist("XPlusX"));
	BOOST_CHECK_EQUAL(calculator.GetValueOfFunction("XPlusX"), 20);

	ExecuteCommand("fn XPlusX_Plus_X=XPlusX+x");
	BOOST_CHECK(calculator.DoesFunctionExist("XPlusX_Plus_X"));
	BOOST_CHECK_EQUAL(calculator.GetValueOfFunction("XPlusX_Plus_X"), 30);
}

BOOST_AUTO_TEST_CASE(cant_declare_function_with_incorrect_name)
{
	calculator.DeclareVariable("x");
	VerifyCommandHandling("fn 1name=x", "Failed to declare function\n");
	VerifyCommandHandling("fn function name=x", "Failed to declare function\n");
	VerifyCommandHandling("fn имяфункции=x", "Failed to declare function\n");

	VerifyCommandHandling("fn 1name=x+x", "Failed to declare function\n");
	VerifyCommandHandling("fn function name=x+x", "Failed to declare function\n");
	VerifyCommandHandling("fn имяфункции=x+x", "Failed to declare function\n");
}

BOOST_AUTO_TEST_CASE(cant_declare_function_if_command_is_entered_incorrectly)
{
	VerifyCommandHandling("fn", "Failed to declare function\n");
	VerifyCommandHandling("fn x", "Failed to declare function\n");
}

BOOST_AUTO_TEST_CASE(can_print_value_of_variable_or_function_if_it_was_declared)
{
	calculator.DeclareVariable("x");
	VerifyCommandHandling("print x", "nan\n");
	calculator.AssignValueToVariable("x", 1.235);
	VerifyCommandHandling("print x", "1.24\n");

	calculator.DeclareFunction("fnX", "x");	
	VerifyCommandHandling("print fnX", "1.24\n");
}

BOOST_AUTO_TEST_CASE(cant_print_value_of_variable_or_function_if_it_hasnt_been_declared)
{
	VerifyCommandHandling("print identifier", "No variable or function with this identifier\n");
}

BOOST_AUTO_TEST_CASE(can_print_names_and_values_of_variables)
{
	calculator.DeclareVariable("x");
	calculator.AssignValueToVariable("y", 1.235);
	calculator.AssignValueToVariable("a", 100.100);

	VerifyCommandHandling("printvars", "a:100.10\nx:nan\ny:1.24\n");
}

BOOST_AUTO_TEST_CASE(can_print_names_and_values_of_functions)
{
	calculator.DeclareVariable("x");
	calculator.AssignValueToVariable("y", 1.236);
	calculator.DeclareFunction("fnX", "x");
	calculator.DeclareFunction("fnY", "y");
	calculator.DeclareFunction("fnA", "y", "fnY", Operation::addition);

	VerifyCommandHandling("printfns", "fnA:2.47\nfnX:nan\nfnY:1.24\n");
}

BOOST_AUTO_TEST_SUITE_END()