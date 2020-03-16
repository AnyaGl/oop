#include "Decoder.h"
#include <iostream>
#include <optional>
#include <vector>

std::optional<char> GetDecodedHtmlEntity(const std::string& str, ptrdiff_t start, long long len)
{
	if (str.compare(start, len, "&quot;") == 0)
	{
		return '"';
	}
	if (str.compare(start, len, "&apos;") == 0)
	{
		return '\'';
	}
	if (str.compare(start, len, "&lt;") == 0)
	{
		return '<';
	}
	if (str.compare(start, len, "&gt;") == 0)
	{
		return '>';
	}
	if (str.compare(start, len, "&amp;") == 0)
	{
		return '&';
	}
	return std::nullopt;
}

std::string HtmlDecode(std::string const& html)
{
	std::string decodingHtml;

	auto it = html.begin();
	while (it != html.end())
	{
		if (*it == '&')
		{
			auto endHtmlEntity = std::find(it, html.end(), ';');
			auto startHtmlEntity = it - html.begin();

			if (endHtmlEntity != html.end() && endHtmlEntity - it < 7)
			{
				auto lengthHtmlEntity = endHtmlEntity - it + 1;
				std::optional<char> decodedSymbol = GetDecodedHtmlEntity(html, startHtmlEntity, lengthHtmlEntity);
				if (decodedSymbol)
				{
					decodingHtml += decodedSymbol.value();
					it = endHtmlEntity + 1;
					continue;
				}
			}
		}
		decodingHtml += *it;
		it += 1;
	}

	return decodingHtml;
}
