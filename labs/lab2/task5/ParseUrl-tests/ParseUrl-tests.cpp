#define CATCH_CONFIG_MAIN
#include "../ParseUrl/ParseUrl.h"
#include "catch2/catch.hpp"

using namespace std::literals;

Protocol protocol;
int port;
std::string host;
std::string document;

Protocol reqProtocol;
int reqPort;
std::string reqHost;
std::string reqDocument;

TEST_CASE("Parse an empty string must be false")
{
	REQUIRE(!ParseURL("", protocol, port, host, document));
}

TEST_CASE("Parse an url must return protocol, port, host and document")
{
	reqProtocol = Protocol::HTTPS;
	reqPort = 123;
	reqHost = "www.mysite";
	reqDocument = "docs/document1.html";

	ParseURL("https://www.mysite:123/docs/document1.html"s, protocol, port, host, document);
	REQUIRE(protocol == reqProtocol);
	REQUIRE(port == reqPort);
	REQUIRE(host == reqHost);
	REQUIRE(document == reqDocument);
}

TEST_CASE("Parse an incorrect url must be false")
{
	REQUIRE(!ParseURL("http:/"s, protocol, port, host, document));
	REQUIRE(!ParseURL("http:/me.com"s, protocol, port, host, document));
}

TEST_CASE("Parse an url with incorrect protocol must be false")
{
	REQUIRE(!ParseURL("htp://my.com"s, protocol, port, host, document));
}

TEST_CASE("Parse an url with incorrect host must be false")
{
	REQUIRE(!ParseURL("http://my.com%"s, protocol, port, host, document));
}

TEST_CASE("Parse an url without port must return default port")
{
	reqPort = 80;
	ParseURL("http://my.com"s, protocol, port, host, document);
	REQUIRE(port == reqPort);

	reqPort = 443;
	ParseURL("https://my.com"s, protocol, port, host, document);
	REQUIRE(port == reqPort);

	reqPort = 21;
	ParseURL("ftp://my.com"s, protocol, port, host, document);
	REQUIRE(port == reqPort);
}

TEST_CASE("Parse an url with incorrect port must be false")
{
	REQUIRE(!ParseURL("http://my.com:-1"s, protocol, port, host, document));
	REQUIRE(!ParseURL("https://my.com:0"s, protocol, port, host, document));
	REQUIRE(!ParseURL("ftp://my.com:65536"s, protocol, port, host, document));
}

TEST_CASE("Parse an url without document must return empty document")
{
	reqDocument = "";

	ParseURL("https://www.mysite:123"s, protocol, port, host, document);
	REQUIRE(document == reqDocument);
}
