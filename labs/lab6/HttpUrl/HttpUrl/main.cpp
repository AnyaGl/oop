#include "HttpUrl.h"
#include "UrlParsingError.h"
#include <iostream>
#include <string>

int main()
{
	std::string input;
	while (getline(std::cin, input))
	{
		try
		{
			CHttpUrl url(input);
			std::cout << "Protocol: " << CHttpUrl::ProtocolToString(url.GetProtocol()) << '\n'
					  << "Domain: " << url.GetDomain() << '\n'
					  << "Port: " << std::to_string(url.GetPort()) << '\n'
					  << "Document: " << url.GetDocument() << '\n'
					  << "url: " << url.GetURL() << '\n';
		}
		catch (const CUrlParsingError& error)
		{
			std::cout << error.what() << std::endl;
		}
		catch (const std::runtime_error& error)
		{
			std::cout << error.what() << std::endl;
		}
	}

	return 0;
}
