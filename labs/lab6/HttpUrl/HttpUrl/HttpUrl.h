#pragma once
#include <string>

enum class Protocol
{
	HTTP,
	HTTPS
};

class CHttpUrl
{
public:
	CHttpUrl(std::string const& url);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol = Protocol::HTTP);
	CHttpUrl(std::string const& domain, std::string const& document, Protocol protocol, unsigned short port);

	std::string GetURL() const;
	std::string GetDomain() const;
	std::string GetDocument() const;
	Protocol GetProtocol() const;
	unsigned short GetPort() const;
	static std::string ProtocolToString(Protocol const& protocol);

private:
	void ParseUrl(const std::string& url);
	static unsigned short GetDefaultPort(Protocol protocol);
	static std::string GetUrlDocument(const std::string& document);
	static Protocol GetProtocol(std::string protocol);
	static unsigned short GetPort(const std::string& port, const Protocol& protocol);

	std::string m_domain;
	std::string m_document;
	Protocol m_protocol;
	unsigned short m_port;
};
