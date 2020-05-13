#include "stdafx.h"
#include "CalculatorControl.h"
#include "Calculator.h"
#include "boost/algorithm/string.hpp"
#include <iomanip>

using namespace std;
using namespace std::placeholders;

struct PartsOfFunction
{
	string name;
	string firstIdentifier;
	string secondIdentifier;
	Operation operation;
};

CCalculatorControl::CCalculatorControl(CCalculator& calculator, std::istream& input, std::ostream& output)
	: m_calculator(calculator)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
			{ "var", bind(&CCalculatorControl::DeclareVariable, this, _1) },
			{ "let", bind(&CCalculatorControl::AssignValueToVariable, this, _1) },
			{ "fn", bind(&CCalculatorControl::FunctionDeclaration, this, _1) },
			{ "print", bind(&CCalculatorControl::PrintIdentifierValue, this, _1) },
			{ "printvars", bind(&CCalculatorControl::PrintVars, this, _1) },
			{ "printfns", bind(&CCalculatorControl::PrintFns, this, _1) },
		})
{
}

bool CCalculatorControl::HandleCommand()
{
	string commandLine;
	getline(m_input, commandLine);
	istringstream strm(commandLine);

	string action;
	strm >> action;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool CCalculatorControl::DeclareVariable(std::istream& args)
{
	string line;
	getline(args, line);
	boost::algorithm::trim_left(line);

	if (!m_calculator.DeclareVariable(line))
	{
		m_output << "Failed to declare a variable\n";		
	}

	return true;
}

bool CanStringBeConvertedToDouble(const string& line)
{
	for (char ch : line)
	{
		if (!isascii(ch) || (!isdigit(ch) && (ch != '.')))
		{
			return false;
		}
	}
	return true;
}
bool ParseAssignValueToVariableCommand(const string& line, string& name, string& identifier, double& value)
{
	vector<string> results;
	boost::split(results, line, [](char ch) {return ch == '='; });

	if (results.size() != 2)
	{
		return false;
	}

	name = results[0];
	char* ptrEnd;
	double valueStrtod = strtod(results[1].c_str(), &ptrEnd);

	if (results[1] != ptrEnd)
	{
		if (!CanStringBeConvertedToDouble(results[1]))
		{
			return false;
		}
		value = valueStrtod;
	}
	else
	{
		identifier = results[1];
	}

	return true;
}

bool CCalculatorControl::AssignValueToVariable(istream& args)
{
	string line;
	string name;
	string identifier;
	double value = NAN;

	getline(args, line);
	boost::algorithm::trim_left(line);

	if (!ParseAssignValueToVariableCommand(line, name, identifier, value))
	{
		m_output << "Failed to assign value to variable\n";
		return true;
	}
		 
	if (!isnan(value) && m_calculator.AssignValueToVariable(name, value))
	{
		return true;
	}	
	else if (m_calculator.AssignValueToVariable(name, identifier))
	{
		return true;
	}

	m_output << "Failed to assign value to variable\n";

	return true;
}

optional<Operation> GetOperation(char operationSymbol)
{ 
	if (operationSymbol == '+')
	{
		return Operation::addition;
	} 
	if (operationSymbol == '-')
	{ 
		return Operation::subtraction; 
	} 
	if (operationSymbol == '*')
	{ 
		return Operation::multiplication; 
	} 
	if (operationSymbol == '/')
	{ 
		return Operation::division; 
	}
	return nullopt;
}

bool ParseFunctionDeclarationCommand(const string& line, PartsOfFunction& function)
{
	vector<string> results;
	boost::split(results, line, boost::algorithm::is_any_of("=+-/*"));

	if (results.size() == 2)
	{
		function.name = results[0];
		function.firstIdentifier = results[1];
		function.secondIdentifier = "";
		function.operation = Operation::noAction;
		return true;
	}

	if (results.size() == 3)
	{
		char operationSymbol = line[line.length() - results[2].length() - 1];
		auto operation = GetOperation(operationSymbol);
		if (!operation)
		{
			return false;
		}
		function.name = results[0];
		function.firstIdentifier = results[1];
		function.secondIdentifier = results[2];
		function.operation = *operation;
		return true;
	}

	return false;
}

bool CCalculatorControl::FunctionDeclaration(std::istream& args)
{
	string line;
	args >> line;
	PartsOfFunction function;
	
	if (!ParseFunctionDeclarationCommand(line, function))
	{
		m_output << "Failed to declare function\n";
		return true;
	}

	if (function.operation == Operation::noAction && m_calculator.FunctionDeclaration(function.name, function.firstIdentifier))
	{
		return true;
	}
	else if (m_calculator.FunctionDeclaration(function.name, function.firstIdentifier, function.secondIdentifier, function.operation))
	{
		return true;
	}

	m_output << "Failed to declare function\n";

	return true;
}

bool CCalculatorControl::PrintIdentifierValue(std::istream& args)
{
	string name;
	args >> name;

	if (m_calculator.DoesVariablesExist(name) || m_calculator.DoesFunctionExist(name))
	{
		double value = m_calculator.GetValue(name);
		if (isnan(value))
		{
			m_output << "nan" << endl;
		}
		else
		{
			m_output << fixed << setprecision(2) << value << endl;
		}
		return true;
	}

	m_output << "No variable or function with this identifier\n";

	return true;
}

bool CCalculatorControl::PrintVars(std::istream&)
{
	CCalculator::Variables variables;
	variables = m_calculator.GetVariablesList();

	for (auto it = variables.begin(); it != variables.end(); it++)
	{
		if (isnan(it->second))
		{
			m_output << it->first << ":" << "nan" << endl;
		}
		else
		{
			m_output << fixed << setprecision(2) << it->first << ":" << it->second << endl;
		}
	}

	return true;
}

bool CCalculatorControl::PrintFns(std::istream&)
{
	CCalculator::Functions functions;
	functions = m_calculator.GetFunctionsList();

	for (auto it = functions.begin(); it != functions.end(); it++)
	{
		if (isnan(it->second.value))
		{
			m_output << it->first << ":" << "nan" << endl;
		}
		else
		{
			m_output << fixed << setprecision(2) << it->first << ":" << it->second.value << endl;
		}
	}

	return true;
}