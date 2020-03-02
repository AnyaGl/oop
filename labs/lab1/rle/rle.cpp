#include <fstream>
#include <iostream>
#include <optional>

typedef double Matrix3x3[3][3];

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

bool PackFile(const std::string& inputFileName)
{
	std::ifstream input;
	input.open(inputFileName, std::ios::binary);
	if (!input.is_open())
	{
		std::cout << inputFileName << " could not be opened\n";
		return true;
	}
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	PackFile(args->inputFileName);

	return 0;
}
