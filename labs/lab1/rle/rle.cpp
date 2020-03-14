#include <fstream>
#include <iostream>
#include <optional>

enum class Mode
{
	pack,
	unpack
};
struct Args
{
	Mode mode;
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

	std::string mode = argv[1];
	if (mode == "pack")
	{
		args.mode = Mode::pack;
	}
	else if (mode == "unpack")
	{
		args.mode = Mode::unpack;
	}
	else
	{
		std::cout
			<< "Invalid mode\n"
			<< "Use: rle.exe pack <input file> <output file>\n or  rle.exe unpack <input file> <output file>\n";
		return std::nullopt;
	}

	args.inputFileName = argv[2];
	args.outputFileName = argv[3];

	return args;
}

void RleCompression(std::istream& input, std::ostream& output)
{
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
		output << (char)counter << ch1;

		counter = 1;
		ch1 = ch2;
	}
}

bool PackFile(const std::string& inputFileName, const std::string& outputFileName)
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

	RleCompression(input, output);

	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return false;
	}
	if (!output.flush())
	{
		std::cout << "Failed to write data to output file\n";
		return false;
	}

	return true;
}

bool RleDecompression(std::istream& input, std::ostream& output)
{
	char ch;
	uint8_t counter;

	while (!input.eof())
	{
		counter = input.get();
		if (!input.eof())
		{	
			input.get(ch);
			if (input.eof() || counter == 0)
			{
				std::cout << "Invalid input file\n";
				return false;
			}
			for (uint8_t i = 0; i < counter; i++)
			{
				output << ch;
			}
		}
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

	if (!RleDecompression(input, output))
	{
		return false;
	}

	if (input.bad())
	{
		std::cout << "Failed to read data from input file\n";
		return false;
	}
	if (!output.flush())
	{
		std::cout << "Failed to write data to output file\n";
		return false;
	}

	return true;
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	if (args->mode == Mode::pack)
	{
		if (!PackFile(args->inputFileName, args->outputFileName))
		{
			return 1;
		}
	}
	else if (args->mode == Mode::unpack)
	{
		if (!UnpackFile(args->inputFileName, args->outputFileName))
		{
			return 1;
		}
	}

	return 0;
}
