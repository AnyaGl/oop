#define CATCH_CONFIG_MAIN
#include "../HTMLDecode/Decoder.h"
#include "catch2/catch.hpp"

TEST_CASE("Сheck the result of ProcessVector()")
{
	std::string html = "Cat &lt;says&gt; &quot;Meow&quot;. M&amp;M&apos;s";
	std::string decodedHtml = "Cat <says> \"Meow\". M&M's";

	CHECK(HtmlDecode(html) == decodedHtml);

	html = "&&&amp;;;";
	decodedHtml = "&&&;;";

	CHECK(HtmlDecode(html) == decodedHtml);
}
