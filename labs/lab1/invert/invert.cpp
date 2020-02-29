#include <fstream>
#include <iostream>
#include <optional>

typedef double Matrix3x3[3][3];

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

void PrintMatrix(const Matrix3x3& matrix)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%.3f ", matrix[i][j]);
		}
		printf("\n");
	}
}

double CountDeterminant(const Matrix3x3& matrix)
{
	double det = matrix[0][0] * matrix[1][1] * matrix[2][2]
		+ matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[0][2] * matrix[1][0] * matrix[2][1]
		- matrix[0][2] * matrix[1][1] * matrix[2][0]
		- matrix[0][1] * matrix[1][0] * matrix[2][2]
		- matrix[0][0] * matrix[1][2] * matrix[2][1];
	return det;
}

void GetUnionMatrix(const Matrix3x3& matrix, Matrix3x3& unionMatrix)
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

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			double eps = 0.0005;
			if (abs(unionMatrix[i][j]) < eps)
			{
				unionMatrix[i][j] = 0;
			}
		}
	}
}

bool GetInvertMatrix(const Matrix3x3& matrix, Matrix3x3& resultMatrix)
{
	double det = CountDeterminant(matrix);
	if (det == 0)
	{
		std::cout << "Determinant is 0. The inverse matrix does not exist.";
		return false;
	}

	GetUnionMatrix(matrix, resultMatrix);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			resultMatrix[i][j] /= det;
		}
	}
	return true;
}

bool ReadMatrixFromFile(std::istream& input, Matrix3x3& matrix)
{
	/*enum State
	{
		Minus,
		Digit,
		Dot,
		Delimiter
	};
	State state;*/

	char ch;
	int i = 0;
	int j = 0;
	int multiplier = 1;
	bool findDot = false;
	std::string intPart, fractPart;

	while (input.get(ch))
	{
		if (ch == '-' && intPart == "" && multiplier == 1)
		{
			multiplier = -1;
		}
		else if (isdigit(ch))
		{
			if (findDot)
			{
				fractPart += ch;
			}
			else
			{
				intPart += ch;
			}
		}
		else if (ch == '.' && !findDot)
		{
			findDot = true;
		}
		else if (ch == ' ' || ch == '\t' || ch == '\n')
		{
			reverse(fractPart.begin(), fractPart.end());
			matrix[i][j] = multiplier * std::atof((intPart + "." + fractPart).c_str());
			intPart = "";
			fractPart = "";
			findDot = false;
			multiplier = 1;
			if (ch == '\n')
			{
				if (j != 2)
				{
					std::cout << "Invalid number of numbers" << '\n';
					return false;
				}
				j = 0;
				i += 1;
			}
			else
			{
				j += 1;
			}
		}
		else
		{
			std::cout << "Invalid character: " << ch << '\n';
			return false;
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

	Matrix3x3 matrix;
	if (!ReadMatrixFromFile(input, matrix))
	{
		return false;
	}
	/*for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			input >> matrix[i][j];
		}
	}*/

	PrintMatrix(matrix);

	Matrix3x3 resultMatrix;
	if (GetInvertMatrix(matrix, resultMatrix))
	{
		std::cout << "result matrix: " << '\n';
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
