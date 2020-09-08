#include "stdafx.h"
#include "../Calculator/Calculator.h"

struct CalculatorFixture
{
	CCalculator calculator;
};

BOOST_FIXTURE_TEST_SUITE(calculator, CalculatorFixture)

BOOST_AUTO_TEST_CASE(can_declare_variable_with_correct_undeclared_name)
{
	BOOST_CHECK(calculator.DeclareVariable("identifier_123"));
	double value = calculator.GetValueOfVariable("identifier_123");
	BOOST_CHECK(calculator.DoesVariablesExist("identifier_123"));
	BOOST_CHECK(isnan(value));
}

BOOST_AUTO_TEST_CASE(cant_declare_variable_with_declared_name)
{
	calculator.DeclareVariable("variable");
	BOOST_CHECK(!calculator.DeclareVariable("variable"));
	calculator.DeclareFunction("function", "variable");
	BOOST_CHECK(!calculator.DeclareVariable("function"));
}

BOOST_AUTO_TEST_CASE(cant_declare_variable_with_incorrect_name)
{
	BOOST_CHECK(!calculator.DeclareVariable(""));
	BOOST_CHECK(!calculator.DeclareVariable("1identifier"));
	BOOST_CHECK(!calculator.DeclareVariable("identi fier"));
	BOOST_CHECK(!calculator.DeclareVariable("identifier!"));
	BOOST_CHECK(!calculator.DeclareVariable("идентификатор"));
}

BOOST_AUTO_TEST_CASE(can_assign_numeric_value_to_variable)
{
	BOOST_CHECK(calculator.AssignValueToVariable("identifier", 100.100));
	double value = calculator.GetValueOfVariable("identifier");
	BOOST_CHECK_EQUAL(value, 100.100);

	BOOST_CHECK(calculator.AssignValueToVariable("identifier", 1.234));
	value = calculator.GetValueOfVariable("identifier");
	BOOST_CHECK_EQUAL(value, 1.234);
}

BOOST_AUTO_TEST_CASE(can_assign_value_of_previously_declared_variable_or_function_to_variable)
{
	calculator.AssignValueToVariable("x", 1.234);
	BOOST_CHECK(calculator.AssignValueToVariable("variableX", "x"));
	double value = calculator.GetValueOfVariable("variableX");
	BOOST_CHECK_EQUAL(value, 1.234);

	calculator.AssignValueToVariable("y", 10);
	calculator.DeclareFunction("function", "y");
	BOOST_CHECK(calculator.AssignValueToVariable("variableY", "function"));
	value = calculator.GetValueOfVariable("variableY");
	BOOST_CHECK_EQUAL(value, 10);
}

BOOST_AUTO_TEST_CASE(cant_assign_variable_value_of_undeclared_identifier)
{
	BOOST_CHECK(!calculator.AssignValueToVariable("variable", "undeclared_identifier"));
}

BOOST_AUTO_TEST_CASE(value_of_variable_doesnt_change_if_value_of_its_argument_has_changed)
{
	calculator.DeclareVariable("y");
	calculator.AssignValueToVariable("x", "y");
	calculator.AssignValueToVariable("y", "10");
	double value = calculator.GetValueOfVariable("x");
	BOOST_CHECK(isnan(value));
}

BOOST_AUTO_TEST_CASE(can_declare_function_of_one_variable)
{
	calculator.DeclareVariable("x");
	BOOST_CHECK(calculator.DeclareFunction("fnX", "x"));
	BOOST_CHECK(calculator.DoesFunctionExist("fnX"));
	double value = calculator.GetValueOfFunction("fnX");
	BOOST_CHECK(isnan(value));

	calculator.AssignValueToVariable("x", 10);
	BOOST_CHECK(calculator.DeclareFunction("function", "fnX"));
	BOOST_CHECK(calculator.DoesFunctionExist("function"));
	value = calculator.GetValueOfFunction("function");
	BOOST_CHECK_EQUAL(value, 10);
}

BOOST_AUTO_TEST_CASE(can_declare_function_of_two_arguments_with_nan_value_if_any_of_its_arguments_has_nan_values)
{
	calculator.AssignValueToVariable("x", 3);

	calculator.DeclareVariable("a");
	BOOST_CHECK(calculator.DeclareFunction("APlusA", "a", "a", Operation::addition));
	BOOST_CHECK(calculator.DoesFunctionExist("APlusA"));
	double value = calculator.GetValueOfFunction("APlusA");
	BOOST_CHECK(isnan(value));
	
	BOOST_CHECK(calculator.DeclareFunction("XPlusA", "x", "a", Operation::addition));
	BOOST_CHECK(calculator.DoesFunctionExist("XPlusA"));
	value = calculator.GetValueOfFunction("XPlusA");
	BOOST_CHECK(isnan(value));
	
	BOOST_CHECK(calculator.DeclareFunction("APlusX", "a", "x", Operation::addition));
	BOOST_CHECK(calculator.DoesFunctionExist("APlusX"));
	value = calculator.GetValueOfFunction("APlusX");
	BOOST_CHECK(isnan(value));
}

BOOST_AUTO_TEST_CASE(can_declare_function_of_two_arguments)
{
	calculator.AssignValueToVariable("x", 3);
	calculator.AssignValueToVariable("y", 4);

	BOOST_CHECK(calculator.DeclareFunction("XPlusY", "x", "y", Operation::addition));
	double value = calculator.GetValueOfFunction("XPlusY");
	BOOST_CHECK_EQUAL(value, 7);

	BOOST_CHECK(calculator.DeclareFunction("XMinusY", "x", "y", Operation::subtraction));
	value = calculator.GetValueOfFunction("XMinusY");
	BOOST_CHECK_EQUAL(value, -1);

	BOOST_CHECK(calculator.DeclareFunction("XMultiplyY", "x", "y", Operation::multiplication));
	value = calculator.GetValueOfFunction("XMultiplyY");
	BOOST_CHECK_EQUAL(value, 12);

	BOOST_CHECK(calculator.DeclareFunction("XDivideY", "x", "y", Operation::division));
	value = calculator.GetValueOfFunction("XDivideY");
	BOOST_CHECK_EQUAL(value, 0.75);

	BOOST_CHECK(calculator.DeclareFunction("XPlusY_Multiply_X", "XPlusY", "x", Operation::multiplication));
	value = calculator.GetValueOfFunction("XPlusY_Multiply_X");
	BOOST_CHECK_EQUAL(value, 21);

	BOOST_CHECK(calculator.DeclareFunction("XPlusY_Plus_XMinusY", "XPlusY", "XMinusY", Operation::addition));
	value = calculator.GetValueOfFunction("XPlusY_Plus_XMinusY");
	BOOST_CHECK_EQUAL(value, 6);
}

BOOST_AUTO_TEST_CASE(cant_declare_function_if_any_of_its_arguments_isnt_declared)
{
	BOOST_CHECK(!calculator.DeclareFunction("name", "x"));
	BOOST_CHECK(!calculator.DeclareFunction("name", "x", "y", Operation::addition));
	calculator.AssignValueToVariable("x", 10);
	BOOST_CHECK(!calculator.DeclareFunction("name", "x", "y", Operation::addition));
}

BOOST_AUTO_TEST_CASE(cant_declare_function_with_declared_name)
{
	calculator.AssignValueToVariable("variable", 10);
	calculator.DeclareFunction("function_of_one_variable", "variable");
	calculator.DeclareFunction("function_of_two_variables", "variable", "variable", Operation::addition);

	BOOST_CHECK(!calculator.DeclareFunction("function_of_one_variable", "variable"));
	BOOST_CHECK(!calculator.DeclareFunction("function_of_two_variables", "variable", "variable", Operation::addition));
}

BOOST_AUTO_TEST_CASE(cant_declare_function_with_incorrect_name)
{
	calculator.AssignValueToVariable("variable", 10);
	BOOST_CHECK(!calculator.DeclareFunction("1name", "variable"));
	BOOST_CHECK(!calculator.DeclareFunction("function name", "variable"));
	BOOST_CHECK(!calculator.DeclareFunction("имяфункции", "variable"));

	BOOST_CHECK(!calculator.DeclareFunction("1name", "variable", "variable", Operation::addition));
	BOOST_CHECK(!calculator.DeclareFunction("function name", "variable", "variable", Operation::addition));
	BOOST_CHECK(!calculator.DeclareFunction("имяфункции", "variable", "variable", Operation::addition));
}

BOOST_AUTO_TEST_CASE(function_Can_change_value_if_any_of_its_arguments_change_values)
{
	calculator.AssignValueToVariable("x", 10);
	calculator.AssignValueToVariable("y", 3);

	calculator.DeclareFunction("fnX", "x");
	calculator.DeclareFunction("XMultiplyY", "x", "y", Operation::multiplication);
	calculator.DeclareFunction("XMultiplyY_Multiply_fnX", "XMultiplyY", "fnX", Operation::multiplication);

	calculator.AssignValueToVariable("x", 20);
	double value = calculator.GetValueOfFunction("fnX");
	BOOST_CHECK_EQUAL(value, 20);
	value = calculator.GetValueOfFunction("XMultiplyY");
	BOOST_CHECK_EQUAL(value, 60);
	value = calculator.GetValueOfFunction("XMultiplyY_Multiply_fnX");
	BOOST_CHECK_EQUAL(value, 1200);
}

BOOST_AUTO_TEST_SUITE_END()