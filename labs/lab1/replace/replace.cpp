#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include "replace.h"

using namespace std;

struct Args {
  string inputFileName;
  string outputFileName;
  string searchString;
  string replaceString;
};

optional<Args> ParseArgs(int argc, char *argv[]) 
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

string replaceSubstring(string newStr, string searchStr, string replaceStr)
{
    size_t foundPos;
    size_t index = 0;
    string resultStr = "";

    while (index < newStr.length()) 
    {
        if (searchStr.length() > 0)
        {
            foundPos = newStr.find(searchStr, index);
            resultStr.append(newStr, index, foundPos - index);
            if (foundPos != string::npos)
            {
                resultStr.append(replaceStr);
                index = foundPos + searchStr.length();
            }
            else
            {
                index = newStr.length();
            }
        }
        else
        {
            resultStr = newStr;
            break;
        }

    }
    resultStr.append("\n");

    return resultStr;
}

void copyFileWithReplace(ifstream& inFile, ofstream& outFile, 
                            string searchStr, string replaceStr)
{
    string currStr; 
    while (getline(inFile, currStr)) 
    {
        outFile << replaceSubstring(currStr, searchStr, replaceStr);
    }
    if (inFile.bad())
    {
        cout << "Failed to read data from input file\n";
        exit(1);
    }
    if (!outFile.flush())
    {
        cout << "Failed to write data to output file\n";
        exit(1);
    }
}

int main(int argc, char *argv[]) 
{

  auto args = ParseArgs(argc, argv);
  if (!args) 
  {
    return 1;
  }

  ifstream inFile;
  inFile.open(args->inputFileName);
  if (!inFile.is_open()) 
  {
    cout << args->inputFileName << " could not be open for reading\n";
    return 1;
  }

  ofstream outFile;
  outFile.open(args->outputFileName);
  if (!outFile.is_open()) 
  {
    cout << args->outputFileName << " could not be open for writing\n";
    return 1;
  }

  string searchStr = args->searchString;
  string replaceStr = args->replaceString;

  copyFileWithReplace(inFile, outFile, searchStr, replaceStr);

  return 0;
}
