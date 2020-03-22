#include "ParseUrl.h"
#include <algorithm>
#include <map>
#include <optional>
#include <regex>

std::map<Protocol, int> defaultPort = {
	{ Protocol::HTTP, 80 },
	{ Protocol::HTTPS, 443 },
	{ Protocol::FTP, 21 },
};

std::optional<Protocol> GetProtocol(std::string protocol)
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
	if (protocol == "ftp")
	{
		return Protocol::FTP;
	}
	return std::nullopt;
}

std::optional<int> GetPort(std::string port, Protocol const& protocol)
{
	if (port.empty())
	{
		return defaultPort[protocol];
	}

	int resultPort;
	resultPort = atoi(port.c_str());
	if (resultPort >= 1 && resultPort <= 65535)
	{
		return resultPort;
	}

	return std::nullopt;
}

bool ParseURL(std::string const& url, Protocol& protocol, int& port, std::string& host, std::string& document)
{
	std::smatch matches;
	std::regex rx("^(.*)://([-.[:alnum:]]+)(:([[:digit:]]+))?(/(.*))?$");
	std::regex_search(url, matches, rx);

	if (matches.empty())
	{
		return false;
	}

	std::optional<Protocol> resultProtocol = GetProtocol(matches[1]);
	if (!resultProtocol)
	{
		return false;
	}
	protocol = resultProtocol.value();

	std::optional<int> resultPort = GetPort(matches[4], protocol);
	if (!resultPort)
	{
		return false;
	}
	port = resultPort.value();

	host = matches[2];
	document = matches[6];

	return true;
}
