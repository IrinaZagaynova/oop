// Invert.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
typedef array<array<double, MATRIX_DIMENSION>, MATRIX_DIMENSION> Matrix3x3;

struct Args
{
	string inputMatrix;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Invalid arguments count\n";
		cout << "Usage: invert.exe <input file>\n";
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
		while (!line.eof())
		{
			if (columnNumber == MATRIX_DIMENSION)
			{
				correctMatrixSize = false;
				break;
			}
			line >> matrix[lineNumber][columnNumber];
			columnNumber++;
		}
		if (columnNumber != MATRIX_DIMENSION)
		{   
			correctMatrixSize = false;
			break;
		}
		lineNumber++;
	}
	if (!correctMatrixSize || (lineNumber < MATRIX_DIMENSION))
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

Matrix3x3 GetAdjugateMatrix(const Matrix3x3& matrix)
{
	Matrix3x3 adjugateMatrix;
	adjugateMatrix[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
	adjugateMatrix[0][1] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
	adjugateMatrix[0][2] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
	adjugateMatrix[1][0] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
	adjugateMatrix[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
	adjugateMatrix[1][2] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
	adjugateMatrix[2][0] = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
	adjugateMatrix[2][1] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
	adjugateMatrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	return adjugateMatrix;
}

Matrix3x3 DivideElementsOfMatrix(const Matrix3x3& adjugateMatrix, double determinant)
{
	Matrix3x3 resultMatrix;
	for (int lineNumber = 0; lineNumber < MATRIX_DIMENSION; lineNumber++)
	{
		for (int columnNumber = 0; columnNumber < MATRIX_DIMENSION; columnNumber++)
		{
			resultMatrix[lineNumber][columnNumber] = adjugateMatrix[lineNumber][columnNumber] / determinant;
		}
	}
	return resultMatrix;
}

bool InvertMatrix(Matrix3x3 matrix, Matrix3x3& resultMatrix)
{
	double determinant;
	determinant = CalculateDeterminant(matrix);
	if (determinant == 0)
	{
		return false;
	}

	Matrix3x3 adjugateMatrix;
	adjugateMatrix = GetAdjugateMatrix(matrix);
	resultMatrix = DivideElementsOfMatrix(adjugateMatrix, determinant);
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

	Matrix3x3 resultMatrix;
	if (!InvertMatrix(matrix, resultMatrix))
	{
		cout << "An inverse matrix does not exist\n";
		return 1;
	}
	PrintMatrix(resultMatrix);

	return 0;
}

