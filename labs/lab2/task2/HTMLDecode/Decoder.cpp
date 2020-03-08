#include "Decoder.h"
#include <optional>

std::optional<char> GetDecodedHtmlEntity(std::string& str)
{
	if (str == "&quot;")
	{
		return '"';
	}
	if (str == "&apos;")
	{
		return '\'';
	}
	if (str == "&lt;")
	{
		return '<';
	}
	if (str == "&gt;")
	{
		return '>';
	}
	if (str == "&amp;")
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
			int startHtmlEntity = it - html.begin();

			if (endHtmlEntity != html.end())
			{
				int lengthHtmlEntity = endHtmlEntity - it + 1;
				std::string htmlEntity = html.substr(startHtmlEntity, lengthHtmlEntity);
				std::optional<char> decodedSymbol = GetDecodedHtmlEntity(htmlEntity);
				if (!decodedSymbol)
				{
					decodingHtml += *it;
					it += 1;
				}
				else
				{
					decodingHtml += decodedSymbol.value();
					it = endHtmlEntity + 1;
				}
			}
			else
			{
				decodingHtml += html.substr(startHtmlEntity, html.end() - it);
				break;
			}
		}
		else
		{
			decodingHtml += *it;
			it += 1;
		}
	}

	return decodingHtml;
}
