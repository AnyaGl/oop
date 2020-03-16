#include "Decoder.h"
#include <iostream>
#include <optional>

using namespace std::literals;

int MAX_LEN_OF_ENTITY = 6;

std::optional<char> GetDecodedHtmlEntity(const std::string& str, ptrdiff_t start)
{
	static const std::string quot = "&quot;"s;
	static const std::string apos = "&apos;"s;
	static const std::string lt = "&lt;"s;
	static const std::string gt = "&gt;"s;
	static const std::string amp = "&amp;"s;

	if (str.compare(start, quot.size(), quot) == 0)
	{
		return '"';
	}
	if (str.compare(start, apos.size(), apos) == 0)
	{
		return '\'';
	}
	if (str.compare(start, lt.size(), lt) == 0)
	{
		return '<';
	}
	if (str.compare(start, gt.size(), gt) == 0)
	{
		return '>';
	}
	if (str.compare(start, amp.size(), amp) == 0)
	{
		return '&';
	}
	return std::nullopt;
}

auto GetEndOfHtmlEntity(const std::string& html, std::string::const_iterator& startFind)
{
	auto endFind = startFind;
	if (html.end() - endFind < MAX_LEN_OF_ENTITY)
	{
		endFind = html.end();
	}
	else
	{
		endFind += MAX_LEN_OF_ENTITY;
	}
	return std::find(startFind, endFind, ';');
}

std::string HtmlDecode(std::string const& html)
{
	std::string decodingHtml;

	auto it = html.begin();
	while (it != html.end())
	{
		if (*it == '&')
		{
			auto endHtmlEntity = GetEndOfHtmlEntity(html, it);
			if (endHtmlEntity != html.end())
			{
				auto startHtmlEntity = it - html.begin();
				std::optional<char> decodedSymbol = GetDecodedHtmlEntity(html, startHtmlEntity);

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
