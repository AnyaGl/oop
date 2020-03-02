#include <fstream>
#include <iostream>
#include <optional>

struct Args
{
	std::string type;
	std::string inputFileName;
	std::string outputFileName;
};

std::optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 4)
	{
		std::cout
			<< "Invalid number of arguments\n"
			<< "Use: rle.exe pack/unpack <input file> <output file>\n";
		return std::nullopt;
	}
	Args args;
	args.type = argv[1];
	args.inputFileName = argv[2];
	args.outputFileName = argv[3];

	return args;
}

bool PackFile(const std::string& inputFileName, std::string& outputFileName)
{
	std::ifstream input;
	input.open(inputFileName, std::ios::binary);
	if (!input.is_open())
	{
		std::cout << inputFileName << " could not be opened\n";
		return false;
	}

	std::ofstream output;
	output.open(outputFileName, std::ios::binary);
	if (!output.is_open())
	{
		std::cout << outputFileName << " could not be opened\n";
		return false;
	}

	char ch1, ch2;
	int counter = 1;

	if (!input.eof())
	{
		input.get(ch1);
	}
	while (!input.eof())
	{
		input.get(ch2);
		while (ch1 == ch2 && counter < 255 && !input.eof())
		{
			counter += 1;
			input.get(ch2);
		}
		output.write((char*)&counter, sizeof(char));
		output.write((char*)&ch1, sizeof(char));
		std::cout << counter << ch1;
		counter = 1;
		ch1 = ch2;
	}
	return true;
}

bool UnpackFile(const std::string& inputFileName, std::string& outputFileName)
{
	std::ifstream input;
	input.open(inputFileName, std::ios::binary);
	if (!input.is_open())
	{
		std::cout << inputFileName << " could not be opened\n";
		return false;
	}

	std::ofstream output;
	output.open(outputFileName, std::ios::binary);
	if (!output.is_open())
	{
		std::cout << outputFileName << " could not be opened\n";
		return false;
	}
}


int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}
	if (args->type == "pack")
	{
		PackFile(args->inputFileName, args->outputFileName);
	}
	else
	{
		UnpackFile(args->inputFileName, args->outputFileName);
	}

	return 0;
}
