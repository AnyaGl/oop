#include <iostream>
#include "Calculator.h"
#include "CalculatorControl.h"

int main()
{
	Calculator calc;
	CalculatorControl control(calc, std::cin, std::cout);

	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "> ";
		if (!control.StartHandler())
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
	return 0;

}