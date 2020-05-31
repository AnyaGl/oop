#include "HttpUrl.h"
#include "UrlParsingError.h"
#include <map>
#include <regex>
#include <stdexcept>

CHttpUrl::CHttpUrl(std::string const& url)
{
	try
	{
		ParseUrl(url);
	}
	catch (const std::invalid_argument& error)
	{
		throw CUrlParsingError(error.what());
	}
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol)
	: CHttpUrl(domain, document, protocol, GetDefaultPort(protocol))
{
}

CHttpUrl::CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port)
{
	if (domain.empty())
	{
		throw std::invalid_argument("Domain mustn't be empty");
	}
	if (port < 1 || port > 65535)
	{
		throw std::invalid_argument("Invalid port. Port must be in segment [1, 65535]");
	}
	m_domain = domain;
	m_document = GetUrlDocument(document);
	m_protocol = protocol;
	m_port = port;
}

std::string CHttpUrl::GetUrlDocument(const std::string& document)
{
	if (document.empty() || document[0] != '/')
	{
		return '/' + document;
	}
	return document;
}

const std::map<Protocol, unsigned short> DEFAULT_PORT = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 }
};

unsigned short CHttpUrl::GetDefaultPort(Protocol protocol)
{
	auto it = DEFAULT_PORT.find(protocol);
	if (it != DEFAULT_PORT.end())
	{
		return it->second;
	}
	throw std::runtime_error("Protocol doesn't have default port");
}

Protocol CHttpUrl::GetProtocol(std::string protocol)
{
	std::transform(protocol.begin(), protocol.begin(), protocol.end(), tolower);
	if (protocol == "http")
	{
		return Protocol::HTTP;
	}
	if (protocol == "https")
	{
		return Protocol::HTTPS;
	}
	throw std::invalid_argument("Invalid protocol");
}

unsigned short CHttpUrl::GetPort(const std::string& port, const Protocol& protocol)
{
	if (port.empty())
	{
		return GetDefaultPort(protocol);
	}

	int resultPort;
	resultPort = atoi(port.c_str());
	if (resultPort >= 1 && resultPort <= 65535)
	{
		return resultPort;
	}
	throw std::invalid_argument("Invalid port. Port must be in segment [1, 65535]");
}

void CHttpUrl::ParseUrl(const std::string& url)
{
	std::smatch matches;
	std::regex rx("^([[:alpha:]]+)://([-.[:alnum:]]+)(:([[:digit:]]+))?(/(.*))?$");
	std::regex_search(url, matches, rx);

	if (matches.empty())
	{
		throw std::invalid_argument("Invalid url. Format: <protocol>://<domain>[:<port>][/<document>]");
	}

	m_protocol = GetProtocol(matches[1]);
	m_domain = matches[2];
	m_port = GetPort(matches[4], m_protocol);
	m_document = GetUrlDocument(matches[6]);
}

std::string CHttpUrl::ProtocolToString(Protocol const& protocol)
{
	if (protocol == Protocol::HTTP)
	{
		return "http";
	}
	if (protocol == Protocol::HTTPS)
	{
		return "https";
	}
	throw std::runtime_error("Protocol string representation doesn't exist");
}

std::string CHttpUrl::GetURL() const
{
	std::string port = (m_port != GetDefaultPort(m_protocol)) ? ":" + std::to_string(m_port) : "";

	return ProtocolToString(m_protocol) + "://" + m_domain + port + m_document;
}

std::string CHttpUrl::GetDomain() const
{
	return m_domain;
}

std::string CHttpUrl::GetDocument() const
{
	return m_document;
}

Protocol CHttpUrl::GetProtocol() const
{
	return m_protocol;
}

unsigned short CHttpUrl::GetPort() const
{
	return m_port;
}
