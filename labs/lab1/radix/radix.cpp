#include <iostream>
#include <optional>
#include <string>

bool IsRadixCorrect(int radix)
{
	const int maxRadix = 'Z' - 'A' + 11;
	if (radix < 2 || radix > maxRadix)
	{
		std::cout << "Invalid radix\n"
				  << "Use radix from range[2, " << maxRadix << "]\n";
		return false;
	}
	return true;
}

struct Args
{
	int sourceRadix = 0;
	int destinationRadix = 0;
	std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout
			<< "Invalid number of arguments\n"
			<< "Use: radix.exe <source notation> <destination notation> <value>\n";
		return std::nullopt;
	}
	Args args;
	args.sourceRadix = std::atoi(argv[1]);
	args.destinationRadix = std::atoi(argv[2]);
	args.value = argv[3];

	return args;
}

bool SafeAdd(int a, int b, int& result)
{
	if (a > 0)
	{
		if (INT_MAX - a < b)
		{
			return false;
		}
	}
	else
	{
		if (INT_MIN - a > b)
		{
			return false;
		}
	}

	result = a + b;
	return true;
}

bool SafeMult(int a, int b, int& result)
{
	if (a > 0)
	{
		if (b > 0)
		{
			if (a > (INT_MAX / b))
			{
				return false;
			}
		}
		else
		{
			if (b < (INT_MIN / a))
			{
				return false;
			}
		}
	}
	else
	{
		if (b > 0)
		{
			if (a < (INT_MIN / b))
			{
				return false;
			}
		}
		else
		{
			if (a != 0 && b < (INT_MAX / a))
			{
				return false;
			}
		}
	}

	result = a * b;
	return true;
}

int GetDigit(char digit, int radix, bool& wasError)
{
	wasError = false;
	int resultDigit = -1;
	char maxDigit;

	if (radix > 10)
	{
		maxDigit = radix - 11 + 'A';
	}
	else
	{
		maxDigit = radix + '0';
	}

	if (digit >= 'A' && digit <= maxDigit)
	{
		resultDigit = digit - 'A' + 10;
	}
	else if (digit >= '0' && digit <= '9' && digit < maxDigit)
	{
		resultDigit = digit - '0';
	}
	else
	{
		wasError = true;
		std::cout << "Invalid character: " << digit << '\n';
	}

	return resultDigit;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	wasError = false;
	if (!IsRadixCorrect(radix))
	{
		wasError = true;
	}
	int resultNumber = 0;
	size_t i = 0;
	bool negativeNum = false;
	if (str[0] == '-')
	{
		negativeNum = true;
		i = 1;
	}

	while (i < str.length() && !wasError)
	{
		int digit = GetDigit(str[i], radix, wasError);

		if (negativeNum && !wasError)
		{
			if (!SafeMult(resultNumber, radix, resultNumber) || !SafeAdd(resultNumber, -digit, resultNumber))
			{
				wasError = true;
				std::cout << "Overflow\n";
			}
		}
		else if (!wasError)
		{
			if (!SafeMult(resultNumber, radix, resultNumber) || !SafeAdd(resultNumber, digit, resultNumber))
			{
				wasError = true;
				std::cout << "Overflow\n";
			}
		}
		i += 1;
	}

	return resultNumber;
}

std::string GetDigit(int digit)
{
	std::string resultStr;
	if (digit > 9)
	{
		resultStr += (char)(digit + 'A' - 10);
	}
	else
	{
		resultStr = std::to_string(digit);
	}
	return resultStr;
}

std::string IntToString(int n, int radix, bool& wasError)
{
	wasError = false;
	if (!IsRadixCorrect(radix))
	{
		wasError = true;
	}

	if (n == 0)
	{
		return "0";
	}

	std::string resultStr;
	int insertPoint = 0;
	bool negativeNum = false;

	if (!wasError)
	{
		if (n < 0)
		{
			negativeNum = true;
		}
		while (n != 0)
		{
			std::string digit = GetDigit(abs(n % radix));

			

			resultStr.insert(0, digit);
			n /= radix;
		}

		if (negativeNum)
		{
			resultStr.insert(0, "-");
		}
	}

	return resultStr;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	bool wasError = false;
	int n = StringToInt(args->value, args->sourceRadix, wasError);
	if (wasError)
	{
		return 1;
	}
	else
	{
		std::cout << IntToString(n, args->destinationRadix, wasError) << '\n';
	}

	return 0;
}
