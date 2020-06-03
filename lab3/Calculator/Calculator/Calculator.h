#pragma once

enum class Operation
{
	addition,
	subtraction,
	multiplication,
	division,
	noAction
};

struct Function
{
	std::string firstIdentifier;
	std::string secondIdentifier;
	Operation operation;
	double value;
};

class CCalculator
{
public:
	typedef std::map<std::string, double> Variables;
	typedef std::map<std::string, Function> Functions;
	bool DeclareVariable(const std::string& identifier);
	bool AssignValueToVariable(const std::string& identifier, double value);
	bool AssignValueToVariable(const std::string& identifier, const std::string& value);
	bool DeclareFunction(const std::string& name, const std::string& identifier);
	bool DeclareFunction(const std::string& name, const std::string& firstIdentifier, const std::string& secondIdentifier, Operation operation);
	bool DoesFunctionExist(const std::string& name)const;
	bool DoesVariablesExist(const std::string& name)const;
	double GetValueOfVariable(const std::string& name)const;
	double GetValueOfFunction(const std::string& name)const;
	double GetValue(const std::string& name)const;
	Variables GetVariablesList()const;
	Functions GetFunctionsList()const;
private:
	typedef std::vector<std::string> FunctionsNames;
	bool IsIdentifierCorrect(const std::string& identifier)const;
	void UpdateFunctionValues(const std::string& identifier, double value);
	void UpdateFunctionOfTwoArguments(const std::string& name, const std::string& firstIdentifier, const std::string& secondIdentifier, Operation operation);
private:
	FunctionsNames m_fnsInOrderOfDeclaration;
	Variables m_variables;
	Functions m_functions;
};