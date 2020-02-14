#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	cout << "Enter input file: ";

	string fileName;
	cin >> fileName;

	ifstream inFile;
	inFile.open(fileName);

	if (!inFile)
	{
		cerr << fileName << " could not be opened!" << endl;
		exit(1);
	}

	cout << "Enter output file: ";

	cin >> fileName;

	ofstream outFile;
	outFile.open(fileName);

	string searchStr, replaceStr;

	cout << "Enter search string: ";
	cin >> searchStr;

	cout << "Enter replace string: ";
	cin >> replaceStr;

	string currStr;
	int index;
	int changeInd = replaceStr.length - searchStr.length;

	while (getline(inFile, currStr))
	{
		index 
	}

	return 0;
}
