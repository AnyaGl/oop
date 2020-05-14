#include "UrlParsingError.h"

CUrlParsingError::CUrlParsingError(const std::string& message)
	: std::invalid_argument(message)
{
}
