// Invert.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string> 
#include <optional>
#include <sstream>
#include <iomanip>

using namespace std;
const int MATRIX_DIMENSION = 3;
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
		while ((line >> matrix[lineNumber][columnNumber]))
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

double СountDeterminant(const Matrix3x3& matrix, double& determinant)
{
	determinant = matrix[0][0] * matrix[1][1] * matrix[2][2] - matrix[0][0] * matrix[1][2] * matrix[2][1]
		        - matrix[0][1] * matrix[1][0] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0]
		        + matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][2] * matrix[1][1] * matrix[2][0];
	return determinant;
}

void GetCofactorMatrix(const Matrix3x3& matrix, Matrix3x3 cofactorMatrix)
{
	cofactorMatrix[0][0] = matrix[1][1] * matrix[2][2] - matrix[1][2] * matrix[2][1];
	cofactorMatrix[0][1] = -(matrix[1][0] * matrix[2][2] - matrix[1][2] * matrix[2][0]);
	cofactorMatrix[0][2] = matrix[1][0] * matrix[2][1] - matrix[1][1] * matrix[2][0];
	cofactorMatrix[1][0] = -(matrix[0][1] * matrix[2][2] - matrix[0][2] * matrix[2][1]);
	cofactorMatrix[1][1] = matrix[0][0] * matrix[2][2] - matrix[0][2] * matrix[2][0];
	cofactorMatrix[1][2] = -(matrix[0][0] * matrix[2][1] - matrix[0][1] * matrix[2][0]);
	cofactorMatrix[2][0] = matrix[0][1] * matrix[1][2] - matrix[0][2] * matrix[1][1];
	cofactorMatrix[2][1] = -(matrix[0][0] * matrix[1][2] - matrix[0][2] * matrix[1][0]);
	cofactorMatrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
}

void GetInvertibleMatrix(Matrix3x3 matrix, const Matrix3x3& adjugateMatrix, double determinant)
{

	for (int lineNumber = 0; lineNumber < MATRIX_DIMENSION; lineNumber++)
	{
		for (int columnNumber = 0; columnNumber < MATRIX_DIMENSION; columnNumber++)
		{
			matrix[columnNumber][lineNumber] = adjugateMatrix[lineNumber][columnNumber] / determinant;
			matrix[lineNumber][columnNumber] = adjugateMatrix[columnNumber][lineNumber] / determinant;
		}
	}
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
	if ((ReadMatrix(args->inputMatrix, matrix)) == false)
	{
		return 1;
	}

	double determinant;
	determinant = СountDeterminant(matrix, determinant);
	if (determinant == 0)
	{
		cout << "An inverse matrix does not exist because the determinant is 0\n";
		return 1;
	}

	Matrix3x3 cofactorMatrix;
	GetCofactorMatrix(matrix, cofactorMatrix);
    GetInvertibleMatrix(matrix, cofactorMatrix, determinant);
	PrintMatrix(matrix);

	return 0;
}

