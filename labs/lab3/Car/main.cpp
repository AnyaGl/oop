#include "Car.h"
#include "CarControl.h"

int main(int argc, char* argv[])
{
	CCar car;
	CCarControl carControl(car, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!carControl.HandleCommand())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	return 0;
}