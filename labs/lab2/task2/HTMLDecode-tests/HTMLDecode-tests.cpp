#define CATCH_CONFIG_MAIN
#include "../HTMLDecode/Decoder.h"
#include "catch2/catch.hpp"

TEST_CASE("Check the result of HtmlDecode(): empty string")
{
	std::string html;
	std::string decodedHtml;

	CHECK(HtmlDecode(html) == decodedHtml);
}

TEST_CASE("Check the result of HtmlDecode(): does not contain html entity")
{
	std::string html = "Hello world!";
	std::string decodedHtml = "Hello world!";

	CHECK(HtmlDecode(html) == decodedHtml);
}

TEST_CASE("Check the result of HtmlDecode()")
{
	std::string html = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string decodedHtml = "Cat <says> \"Meow\". M&M's";

	CHECK(HtmlDecode(html) == decodedHtml);

	html = "&&&amp;;;";
	decodedHtml = "&&&;;";

	CHECK(HtmlDecode(html) == decodedHtml);
}
