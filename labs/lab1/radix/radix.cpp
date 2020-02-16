#include <iostream>
#include <string>
#include <optional>

struct Args {
    int sourceRadix;
    int destinationRadix;
    std::string value;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Invalid number of arguments\n"
            << "Use: radix.exe <source notation> <destination notation> <value>\n";
        return std::nullopt;
    }
    Args args;
    args.sourceRadix = std::atoi(argv[1]);
    args.destinationRadix = std::atoi(argv[2]);
    args.value = argv[3];

    if (args.sourceRadix < 2 || args.sourceRadix > 36 ||
        args.destinationRadix < 2 || args.destinationRadix > 36)
    {
        std::cout << "Invalid radix\n"
            << "Use radix from range[2, 36]\n";
        return std::nullopt;
    }
    return args;
}

int GetDigit(char digit, int radix, bool& wasError)
{
    char maxLetter = radix - 11 + 'A';
    int resultDigit = -1;

    if (digit >= 'A' && digit <= maxLetter)
    {
        resultDigit = digit - 'A' + 10;
    }
    else
    {
        if (digit >= '0' && digit <= '9')
        {
            resultDigit = digit - '0';
        }
        else
        {
            wasError = true;
            std::cout << "Invalid character: " << digit << '\n';
        }
    }

    return resultDigit;
}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
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
        int n = GetDigit(str[i], radix, wasError);

        if (negativeNum)
        {
            if (INT_MIN - resultNumber <= (-1 * n * (int)pow(radix, str.length() - i - 1)))
            {
                resultNumber -= n * (int)pow(radix, str.length() - i - 1);
            }
            else
            {
                wasError = true;
                std::cout << "Overflow\n";
            }
        }
        else
        {
            if (INT_MAX - resultNumber >= (n * (int)pow(radix, str.length() - i - 1)))
            {
                resultNumber += n * (int)pow(radix, str.length() - i - 1);
            }
            else
            {
                wasError = true;
                std::cout << "Overflow\n";
            }
        }
        i += 1;
    }

    return resultNumber;
}

std::string IntToString(int n, int radix, bool& wasError)
{
    std::string resultStr = "";
    int insertPoint = 0;
    bool negativeNum = false;
    if (n < 0)
    {
        negativeNum = true;
    }

    while (n != 0)
    {
        std::string digit;
        if (abs(n % radix) > 9)
        {
            digit = std::to_string(abs(n % radix) + 'A' - 10);
        }
        else
        {
            digit = std::to_string(abs(n % radix));
        }
        resultStr.insert(0, digit);
        n /= radix;
    }

    if (negativeNum)
    {
        resultStr.insert(0, "-");
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