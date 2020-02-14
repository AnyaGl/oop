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

  if (!inFile) {
    cerr << argv[1] << " could not be opened!" << endl;
    exit(1);
  }

  ofstream outFile;
  outFile.open(argv[2]);

  string searchStr = argv[3];
  string replaceStr = argv[4];

  string currStr;
  int index;
  int changeInd = replaceStr.length() - searchStr.length();

  while (getline(inFile, currStr)) {
    cout << currStr;
  }

  return 0;
}
