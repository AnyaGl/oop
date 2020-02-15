#include <fstream>
#include <iostream>
#include <optional>
#include <string>

using namespace std;

struct Args {
  string inputFileName;
  string outputFileName;
  string searchString;
  string replaceString;
};

optional<Args> ParseArgs(int argc, char *argv[]) {
  if (argc != 5) {
    cout << "Error: number of arguments\n"
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

int main(int argc, char *argv[]) {

  auto args = ParseArgs(argc, argv);
  if (!args) {
    return 1;
  }

  ifstream inFile;
  inFile.open(args->inputFileName);
  if (!inFile.is_open()) {
    cout << args->inputFileName << " could not be opened!\n";
    return 1;
  }

  ofstream outFile;
  outFile.open(args->outputFileName);
  if (!outFile.is_open()) {
    cout << args->outputFileName << " could not be opened!\n";
    return 1;
  }

  string searchStr = args->searchString;
  string replaceStr = args->replaceString;

  string currStr, resultStr;
  int index, foundPos;

  while (getline(inFile, currStr)) {
    index = 0;
    resultStr = "";

    while (index < currStr.length()) {
      foundPos = currStr.find(searchStr, index);

      resultStr.append(currStr, index, foundPos - index);

      if (foundPos != string::npos) {
        resultStr.append(replaceStr);
        index = foundPos + searchStr.length();
      } else {
        index = currStr.length();
      }
    }
    outFile << resultStr << '\n';
  }

  return 0;
}
