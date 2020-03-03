#include <fstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>

typedef double Matrix3x3[3][3];

struct Args
{
	std::string matrixFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout
			<< "Invalid number of arguments\n"
			<< "Use: invert.exe <matrix file1>\n";
		return std::nullopt;
	}
	Args args;
	args.matrixFileName = argv[1];

	return args;
}

void PrintMatrix(const Matrix3x3& matrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << std::fixed << std::setprecision(3) << matrix[i][j] << " ";
		}
		std::cout << '\n';
	}
}

double GetDeterminant(const Matrix3x3& matrix)
{
	double det = matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[0][2] * matrix[1][0] * matrix[2][1]
		- matrix[0][2] * matrix[1][1] * matrix[2][0]
		- matrix[0][1] * matrix[1][0] * matrix[2][2]
		- matrix[0][0] * matrix[1][2] * matrix[2][1];
	return det;
}

void GetAdjugateMatrix(const Matrix3x3& matrix, Matrix3x3& adjugateMatrix)
{
	adjugateMatrix[0][0] = matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2];
	adjugateMatrix[1][0] = -(matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2]);
	adjugateMatrix[2][0] = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];

	adjugateMatrix[0][1] = -(matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2]);
	adjugateMatrix[1][1] = matrix[0][0] * matrix[2][2] - matrix[2][0] * matrix[0][2];
	adjugateMatrix[2][1] = -(matrix[0][0] * matrix[2][1] - matrix[2][0] * matrix[0][1]);

	adjugateMatrix[0][2] = matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2];
	adjugateMatrix[1][2] = -(matrix[0][0] * matrix[1][2] - matrix[1][0] * matrix[0][2]);
	adjugateMatrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];
}

bool ReadMatrixFromFile(const std::string& matrixFileName, Matrix3x3& matrix)
{
	std::ifstream input;
	input.open(matrixFileName);
	if (!input.is_open())
	{
		std::cout << matrixFileName << " could not be open for reading\n";
		return false;
	}
	int i = 0;
	int j = 0;
	double number;
	std::string str;

	while (!input.eof() && i < 3)
	{
		j = 0;
		std::getline(input, str);
		std::stringstream line(str);
		while (line >> number && j < 3)
		{
			matrix[i][j] = number;
			j += 1;
		}
		if (j != 3)
		{
			break;
		}
		i += 1;
	}

	if (i != 3)
	{
		std::cout << "Invalid matrix" << '\n';
		return false;
	}

	return true;
}

void MultiplyMatrixByNumber(Matrix3x3& resultMatrix, double num)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			resultMatrix[i][j] *= num;
		}
	}
}

bool InvertMatrix(const Matrix3x3& matrix, Matrix3x3& resultMatrix)
{
	double det = GetDeterminant(matrix);
	if (det == 0)
	{
		std::cout << "Determinant is 0. The inverse matrix does not exist.\n";
		return false;
	}

	GetAdjugateMatrix(matrix, resultMatrix);

	MultiplyMatrixByNumber(resultMatrix, 1 / det);

	return true;
}

int main(int argc, char* argv[])
{

	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	Matrix3x3 matrix;
	if (!ReadMatrixFromFile(args->matrixFileName, matrix))
	{
		return 1;
	}
	Matrix3x3 resultMatrix;
	if (!InvertMatrix(matrix, resultMatrix))
	{
		return 0;
	}
	PrintMatrix(resultMatrix);
	return 0;
}