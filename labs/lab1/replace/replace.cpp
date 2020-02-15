#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {

  if (argc != 5) {
    cout << "Error: number of arguments\n"
         << "Use: replace.exe <input file> <output file> <search string> "
            "<replace string>\n";
    return 1;
  }

  ifstream inFile;
  inFile.open(argv[1]);
  if (!inFile.is_open()) {
    cout << argv[1] << " could not be opened!\n";
    return 1;
  }

  ofstream outFile;
  outFile.open(argv[2]);
  if (!outFile.is_open()) {
      cout << argv[2] << " could not be opened!\n";
      return 1;
  }

  string searchStr = argv[3];
  string replaceStr = argv[4];

  string currStr, resultStr;
  int index, foundPos;
  int changeInd = replaceStr.length() - searchStr.length();

  while (getline(inFile, currStr)) {
    index = 0;
    resultStr = "";

    while (index < currStr.length()) {
        foundPos = currStr.find(searchStr, index);
        
        resultStr.append(currStr, index, foundPos - index);

        if (foundPos != string::npos) {
            resultStr.append(replaceStr);
            index = foundPos + searchStr.length();
        }
        else {
            index = currStr.length();
        }
        
    }
    outFile << resultStr << '\n';
  }

  return 0;
}
