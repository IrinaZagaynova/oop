﻿// Invert.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string> 
#include <optional>
#include <sstream>
#include <array>
#include <iomanip>

using namespace std;
const int MATRIX_DIMENSION = 3;
//typedef array<array<double, MATRIX_DIMENSION>, MATRIX_DIMENSION> Matrix3x3;
typedef double Matrix3x3[MATRIX_DIMENSION][MATRIX_DIMENSION];

struct Args
{
	string inputMatrix;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: compare.exe <input file>\n";
		return nullopt;
	}
	Args args;
	args.inputMatrix = argv[1];
	return args;
}

bool ReadMatrix(const string& inputMatrix, Matrix3x3& matrix)
{
	ifstream input(inputMatrix);
	if (!input.is_open())
	{
		cout << "Failed to open " << inputMatrix << " for reading\n";
		return false;
	}

	int lineNumber = 0, columnNumber;
	string str;
	bool correctMatrixSize = true;
	while (getline(input, str) && correctMatrixSize)
	{
		columnNumber = 0;
		if (lineNumber == MATRIX_DIMENSION)
		{
			correctMatrixSize = false;
			break;
		}
		stringstream line(str);
		while (line >> matrix[lineNumber][columnNumber])
		{
			columnNumber++;
		}
		if (columnNumber != MATRIX_DIMENSION)
		{   
			correctMatrixSize = false;
			break;
		}
		lineNumber++;
	}
	if (lineNumber < MATRIX_DIMENSION)
	{
		correctMatrixSize = false;
	}
	if (!correctMatrixSize)
	{
		cout << "Input must be a 3x3 dimensional matrix of numbers\n";
		return false;
	}
	if (input.bad())
	{
		cout << "Failed to read data from " << inputMatrix << "\n";
		return false;
	}

	return true;
}

double CalculateDeterminant(const Matrix3x3& matrix)
{
	double determinant;
	determinant = matrix[0][0] * matrix[1][1] * matrix[2][2] - matrix[0][0] * matrix[1][2] * matrix[2][1]
		        - matrix[0][1] * matrix[1][0] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0]
		        + matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][2] * matrix[1][1] * matrix[2][0];
	return determinant;
}

void GetAdjugateMatrix(const Matrix3x3& matrix, Matrix3x3& adjugateMatrix)
{
	adjugateMatrix[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
	adjugateMatrix[0][1] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
	adjugateMatrix[0][2] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
	adjugateMatrix[1][0] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
	adjugateMatrix[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
	adjugateMatrix[1][2] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
	adjugateMatrix[2][0] = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
	adjugateMatrix[2][1] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
	adjugateMatrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

bool GetInvertibleMatrix(Matrix3x3& matrix)
{

	double determinant;
	determinant = CalculateDeterminant(matrix);
	if (determinant == 0)
	{
		cout << "An inverse matrix does not exist because the determinant is 0\n";
		return false;
	}

	Matrix3x3 adjugateMatrix;
	GetAdjugateMatrix(matrix, adjugateMatrix);

	for (int lineNumber = 0; lineNumber < MATRIX_DIMENSION; lineNumber++)
	{
		for (int columnNumber = 0; columnNumber < MATRIX_DIMENSION; columnNumber++)
		{
			matrix[lineNumber][columnNumber] = adjugateMatrix[lineNumber][columnNumber] / determinant;
		}
	}

	return true;
}

void PrintMatrix(const Matrix3x3& matrix)
{
	for (int lineNumber = 0; lineNumber < MATRIX_DIMENSION; lineNumber++)
	{
		for (int columnNumber = 0; columnNumber < MATRIX_DIMENSION; columnNumber++)
		{
			cout << fixed << setprecision(3) << matrix[lineNumber][columnNumber];
			if (columnNumber < 2)
			{
				cout << " ";
			}
		}
		cout << "\n";
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	Matrix3x3 matrix;
	if (!ReadMatrix(args->inputMatrix, matrix))
	{
		return 1;
	}
	if (!GetInvertibleMatrix(matrix))
	{
		return 1;
	}
	PrintMatrix(matrix);

	return 0;
}

