#include "HttpUrl.h"

CHttpUrl::CHttpUrl(std::string const& url)
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
}

std::string CHttpUrl::GetURL() const
{
	return std::string();
}

std::string CHttpUrl::GetDomain() const
{
	return std::string();
}

std::string CHttpUrl::GetDocument() const
{
	return std::string();
}

Protocol CHttpUrl::GetProtocol() const
{
	return Protocol();
}

unsigned short CHttpUrl::GetPort() const
{
	return 0;
}
