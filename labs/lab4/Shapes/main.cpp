#include "ProcessShapes.h"
#include <iostream>
#include <string>
int main()
{
	CProcessShapes process(std::cin, std::cout);

	std::string commandLine;
	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!process.HandleCommand())
		{
			std::cout << "Unknown command!\n";
		}
	}
	process.PrintShapeWithMaxArea();
	process.PrintShapeWithMinPerimeter();
	process.DrawShapes();
	return 0;
}
