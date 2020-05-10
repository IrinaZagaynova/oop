#include "stdafx.h"
#include "Calculator.h"

bool CCalculator::IsIdentifierСorrect(const std::string& identifier)const
{
	if (!isascii(identifier[0]) || identifier.empty() || isdigit(identifier[0]))
	{
		return false;
	}

	for (char ch : identifier)
	{
		if (!isascii(ch) || (!isalpha(ch) && !isdigit(ch) && ch != '_'))
		{
			return false;
		}
	}

	return true;
}

bool CCalculator::DoesFunctionExist(const std::string& name)const
{
	return m_functions.find(name) != m_functions.end();
}

bool CCalculator::DoesVariablesExist(const std::string& name)const
{
	return m_variables.find(name) != m_variables.end();
}

bool CCalculator::DeclareVariable(const std::string& identifier)
{
	if (DoesVariablesExist(identifier) || DoesFunctionExist(identifier) || !IsIdentifierСorrect(identifier))
	{
		return false;
	}

	m_variables.emplace(identifier, NAN);
	return true;
}

double CCalculator::GetValueOfVariable(const std::string& name)const
{
	auto it = m_variables.find(name);
	return it->second;
	if (it != m_variables.end())
	{
		return it->second;
	}
	return NAN;
}

double CCalculator::GetValueOfFunction(const std::string& name)const
{
	auto it = m_functions.find(name);
	if (it != m_functions.end())
	{
		return it->second.value;
	}
	return NAN;
}

double CCalculator::GetValue(const std::string& name)const
{
	if (DoesVariablesExist(name))
	{
		return GetValueOfVariable(name);
	}
	if (DoesFunctionExist(name))
	{
		return GetValueOfFunction(name);
	}
	return NAN;
}

bool CCalculator::AssignValueToVariable(const std::string& identifier, double value)
{
	auto itVariable = m_variables.find(identifier);
	
	if (itVariable != m_variables.end())
	{
		itVariable->second = value;
		UpdateFunctionValues(identifier, value);
	}
	else
	{
		if (!IsIdentifierСorrect(identifier))
		{
			return false;
		}

		m_variables.emplace(identifier, value);
	}

	return true;
}

bool CCalculator::AssignValueToVariable(const std::string& variable, const std::string& identifier)
{
	if (!IsIdentifierСorrect(variable) || (!DoesVariablesExist(identifier) && !DoesFunctionExist(identifier)))
	{
		return false;
	}

	double value = GetValue(identifier);
	m_variables.emplace(variable, value);
	UpdateFunctionValues(variable, value);

	return true;
}

bool CCalculator::FunctionDeclaration(const std::string& name, const std::string& identifier)
{
	if (!IsIdentifierСorrect(name) || DoesVariablesExist(name) || DoesFunctionExist(name))
	{
		return false;
	}

	if (!DoesVariablesExist(identifier) && !DoesFunctionExist(identifier))
	{
		return false;
	}

	double value = GetValue(identifier);
	Function function = { identifier, "", Operation::noAction, value };
	m_functions.emplace(name, function);
	m_fnsInOrderOfDeclaration.push_back(name);

	return true;
}

bool CCalculator::FunctionDeclaration(const std::string& name, const std::string& firstIdentifier, const std::string& secondIdentifier, Operation operation)
{
	if (!IsIdentifierСorrect(name) || DoesVariablesExist(name) || DoesFunctionExist(name))
	{
		return false;
	}

	if (!(DoesVariablesExist(firstIdentifier) || DoesFunctionExist(firstIdentifier)) 
		|| !(DoesVariablesExist(secondIdentifier) || DoesFunctionExist(secondIdentifier)))
	{
		return false;
	}

	double firstIdentifierValue = GetValue(firstIdentifier);
	double secondIdentifierValue = GetValue(secondIdentifier);

	double value = СalculateValue(firstIdentifierValue, secondIdentifierValue, operation);
	Function function = { firstIdentifier, secondIdentifier, operation, value };
	m_functions.emplace(name, function);
	m_fnsInOrderOfDeclaration.push_back(name);

	return true;
}

double CCalculator::СalculateValue(double firstArgument, double secondArgument, Operation operation)const
{
	if (isnan(secondArgument) || isnan(secondArgument))
	{
		return NAN;
	}

	switch (operation)
	{
	case Operation::addition:
		return firstArgument + secondArgument;
	case Operation::subtraction:
		return firstArgument - secondArgument;
	case Operation::multiplication:
		return firstArgument * secondArgument;
	case Operation::division:
		return firstArgument / secondArgument;
	}
	return NAN;
}

void CCalculator::UpdateFunctionOfTwoArguments(const std::string& name, const std::string& firstIdentifier, const std::string& secondIdentifier, Operation operation)
{
	double functionValue = СalculateValue(GetValue(firstIdentifier), GetValue(secondIdentifier), operation);

	auto it = m_functions.find(name);
	it->second.value = functionValue;
}

void CCalculator::UpdateFunctionValues(const std::string& identifier, double value)
{
	for (auto it = m_functions.begin(); it != m_functions.end(); it++)
	{
		if (it->second.firstIdentifier == identifier)
		{
			it->second.value = value;
		}
	}

	for (auto name : m_fnsInOrderOfDeclaration)
	{
		auto it = m_functions.find(name);
		if (it->second.secondIdentifier == "")
		{
			it->second.value = GetValue(it->second.firstIdentifier);
		}
		else
		{
			UpdateFunctionOfTwoArguments(it->first, it->second.firstIdentifier, it->second.secondIdentifier, it->second.operation);
		}
	}
}

CCalculator::Variables CCalculator::GetVariablesList()const
{
	return m_variables;
}

CCalculator::Functions CCalculator::GetFunctionsList()const
{
	return m_functions;
}
