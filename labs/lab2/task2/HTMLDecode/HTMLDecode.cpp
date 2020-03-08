#include "Decoder.h"
#include <iostream>

int main()
{
	std::string line;
	while (getline(std::cin, line))
	{
		std::string decodedString = HtmlDecode(line);
		std::cout << decodedString;
	}
}
