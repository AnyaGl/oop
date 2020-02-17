#include <fstream>
#include <iostream>
#include <optional>
#include <string>

using namespace std;

struct Args
{
	string inputFileName;
	string outputFileName;
	string searchString;
	string replaceString;
};

optional<Args> ParseArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid number of arguments\n"
			 << "Use: replace.exe <input file> <output file> <search string> "
				"<replace string>\n";
		return nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];
	return args;
}

string ReplaceSubstring(const string& str, const string& searchStr, const string& replaceStr)
{
	size_t foundPos;
	size_t index = 0;
	string resultStr;

	if (searchStr.length() > 0)
	{
		while (index < str.length())
		{
			foundPos = str.find(searchStr, index);
			if (foundPos != string::npos)
			{
				resultStr.append(str, index, foundPos - index);
				resultStr.append(replaceStr);
				index = foundPos + searchStr.length();
			}
			else
			{
				resultStr.append(str, index, str.length());
				break;
			}
		}
	}
	else
	{
		resultStr = str;
	}

	return resultStr;
}

void CopyFileWithReplace(istream& inFile, ostream& outFile,
	const string& searchStr, const string& replaceStr, bool& wasError)
{
	string currStr;
	while (getline(inFile, currStr))
	{
		outFile << ReplaceSubstring(currStr, searchStr, replaceStr) << '\n';
	}
	if (inFile.bad())
	{
		cout << "Failed to read data from input file\n";
		wasError = true;
		return;
	}
	if (!outFile.flush())
	{
		cout << "Failed to write data to output file\n";
		wasError = true;
		return;
	}
}

void OpenAndCopyFileWithReplace(const string& inFileName, const string& outFileName,
	const string& searchStr, const string& replaceStr, bool& wasError)
{
	ifstream inFile;
	inFile.open(inFileName);
	if (!inFile.is_open())
	{
		cout << inFileName << " could not be open for reading\n";
		wasError = true;
		return;
	}

	ofstream outFile;
	outFile.open(outFileName);
	if (!outFile.is_open())
	{
		cout << outFileName << " could not be open for writing\n";
		wasError = true;
		return;
	}

	CopyFileWithReplace(inFile, outFile, searchStr, replaceStr, wasError);
}

int main(int argc, char* argv[])
{
	auto args = ParseArgs(argc, argv);
	if (!args)
	{
		return 1;
	}

	bool wasError = false;
	OpenAndCopyFileWithReplace(args->inputFileName, args->outputFileName,
		args->searchString, args->replaceString, wasError);

	if (wasError)
	{
		return 1;
	}

	return 0;
}
