#define CATCH_CONFIG_MAIN
#include "../HttpUrl/HttpUrl.h"
#include "catch2/catch.hpp"

TEST_CASE("Constructor that takes URL must parse it")
{
	CHttpUrl url("https://www.mysite:123/docs/document1.html");
	CHECK(url.GetDomain() == "www.mysite");
	CHECK(url.GetDocument() == "/docs/document1.html");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == 123);

	SECTION("If failed, an exception must be thrown")
	{
		CHECK_THROWS(CHttpUrl("http:/my.com"));
		CHECK_THROWS(CHttpUrl("httpk://my.com"));
		CHECK_THROWS(CHttpUrl("http://my.com:65536"));
	}
}

TEST_CASE("Constructor, that takes domain, document, [protocol], must initialize url")
{
	CHttpUrl url("www.mysite", "/doc", Protocol::HTTPS);
	CHECK(url.GetDomain() == "www.mysite");
	CHECK(url.GetDocument() == "/doc");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == 443);

	SECTION("Default protocol must be HTTP")
	{
		CHttpUrl url1("www.mysite", "/doc");
		CHECK(url1.GetProtocol() == Protocol::HTTP);
	}

	SECTION("If document doesn't start with '/', then constructor must add '/'")
	{
		CHttpUrl url1("www.mysite", "doc");
		CHECK(url1.GetDocument() == "/doc");

		CHttpUrl url2("www.mysite", "");
		CHECK(url2.GetDocument() == "/");
	}

	SECTION("If failed, an exception must be thrown")
	{
		CHECK_THROWS(CHttpUrl("", "/doc"));
	}
}

TEST_CASE("Constructor, that takes domain, document, protocol, port, must initialize url")
{
	CHttpUrl url("www.mysite", "/doc", Protocol::HTTPS, 123);
	CHECK(url.GetDomain() == "www.mysite");
	CHECK(url.GetDocument() == "/doc");
	CHECK(url.GetProtocol() == Protocol::HTTPS);
	CHECK(url.GetPort() == 123);

	SECTION("If document doesn't start with '/', then constructor must add '/'")
	{
		CHttpUrl url1("www.mysite", "doc", Protocol::HTTPS, 123);
		CHECK(url1.GetDocument() == "/doc");

		CHttpUrl url2("www.mysite", "", Protocol::HTTPS, 123);
		CHECK(url2.GetDocument() == "/");
	}

	SECTION("If failed, an exception must be thrown")
	{
		CHECK_THROWS(CHttpUrl("", "/doc", Protocol::HTTPS, 123));
		CHECK_THROWS(CHttpUrl("www.mysite", "/doc", Protocol::HTTPS, (short)65536));
		CHECK_THROWS(CHttpUrl("www.mysite", "/doc", Protocol::HTTP, 0));
	}
}

TEST_CASE("GetUrl() must return url string representation")
{
	CHttpUrl url1("www.mysite", "doc", Protocol::HTTPS, 123);
	CHECK(url1.GetURL() == "https://www.mysite:123/doc");

	SECTION("Standard port for HTTP and HTTPS mustn't be included in string")
	{
		CHttpUrl url2("www.mysite", "doc", Protocol::HTTP);
		CHECK(url2.GetURL() == "http://www.mysite/doc");
	}
}

TEST_CASE("If port is not specified, then it must be default for HTTP and HTTPS")
{
	CHttpUrl url1("www.mysite", "doc", Protocol::HTTP);
	CHttpUrl url2("www.mysite", "doc", Protocol::HTTPS);
	CHECK(url1.GetPort() == 80);
	CHECK(url2.GetPort() == 443);
}
