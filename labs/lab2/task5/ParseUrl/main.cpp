#include "ParseUrl.h"
#include <iostream>

void PrintUrlInfo(std::string const& host, int port, std::string const& document)
{
	std::cout << "HOST: " << host << '\n';
	std::cout << "PORT: " << port << '\n';
	std::cout << "DOC: " << document << '\n';
}

int main()
{
	std::string url;
	Protocol protocol;
	int port;
	std::string host;
	std::string document;

	while (getline(std::cin, url))
	{
		if (ParseURL(url, protocol, port, host, document))
		{
			PrintUrlInfo(host, port, document);
		}
		else
		{
			std::cout << "Incorrect URL\n";
		}
	}

	return 0;
}
