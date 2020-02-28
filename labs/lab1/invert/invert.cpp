#include <fstream>
#include <iostream>
#include <optional>

const int matrixSize = 3;

struct Args
{
	std::string inputFileName;
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
	args.inputFileName = argv[1];

	return args;
}

void PrintMatrix(double (&matrix)[matrixSize][matrixSize])
{
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			printf("%.3f ", matrix[i][j]);
		}
		printf("\n");
	}
}

double CountDeterminant(const double (&matrix)[3][3])
{
	double det = matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[0][2] * matrix[1][0] * matrix[2][1]
		- matrix[0][2] * matrix[1][1] * matrix[2][0]
		- matrix[0][1] * matrix[1][0] * matrix[2][2]
		- matrix[0][0] * matrix[1][2] * matrix[2][1];
	return det;
}

void GetUnionMatrix(double (&matrix)[matrixSize][matrixSize], double (&unionMatrix)[matrixSize][matrixSize])
{
	unionMatrix[0][0] = matrix[1][1] * matrix[2][2] - matrix[2][1] * matrix[1][2];
	unionMatrix[1][0] = -(matrix[1][0] * matrix[2][2] - matrix[2][0] * matrix[1][2]);
	unionMatrix[2][0] = matrix[1][0] * matrix[2][1] - matrix[2][0] * matrix[1][1];

	unionMatrix[0][1] = -(matrix[0][1] * matrix[2][2] - matrix[2][1] * matrix[0][2]);
	unionMatrix[1][1] = matrix[0][0] * matrix[2][2] - matrix[2][0] * matrix[0][2];
	unionMatrix[2][1] = -(matrix[0][0] * matrix[2][1] - matrix[2][0] * matrix[0][1]);

	unionMatrix[0][2] = matrix[0][1] * matrix[1][2] - matrix[1][1] * matrix[0][2];
	unionMatrix[1][2] = -(matrix[0][0] * matrix[1][2] - matrix[1][0] * matrix[0][2]);
	unionMatrix[2][2] = matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1];

	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			double eps = 0.001;
			if (abs(unionMatrix[i][j]) <= eps)
			{
				unionMatrix[i][j] = 0;			
			}
		}
	}
}

bool GetInvertMatrix(double (&matrix)[matrixSize][matrixSize], double (&resultMatrix)[matrixSize][matrixSize])
{
	double det = CountDeterminant(matrix);
	if (det == 0)
	{
		std::cout << "Determinant is 0. The inverse matrix does not exist.";
		return false;
	}

	GetUnionMatrix(matrix, resultMatrix);

	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			resultMatrix[i][j] /= det;
		}
	}
	return true;
}

bool InvertMatrixFromFile(const std::string& inputFileName)
{
	std::ifstream input;
	input.open(inputFileName);
	if (!input.is_open())
	{
		std::cout << inputFileName << " could not be open for reading\n";
		return false;
	}

	double matrix[matrixSize][matrixSize];
	for (int i = 0; i < matrixSize; i++)
	{
		for (int j = 0; j < matrixSize; j++)
		{
			input >> matrix[i][j];
		}
	}

	double resultMatrix[matrixSize][matrixSize];
	if (GetInvertMatrix(matrix, resultMatrix))
	{
		PrintMatrix(resultMatrix);
		return true;
	}

	return false;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}
	if (!InvertMatrixFromFile(args->inputFileName))
	{
		return 1;
	}
	return 0;
}
