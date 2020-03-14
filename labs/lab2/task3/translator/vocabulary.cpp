#include "vocabulary.h"
#include <algorithm>

bool IsRusWord(const std::string& word)
{
	for (char ch : word)
	{
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		{
			return false;
		}
	}
	return true;
}

std::optional<ListOfWords> GetRusTranslation(std::string word, Vocabulary& vocabulary)
{
	if (vocabulary.find(word) == vocabulary.end())
	{
		return std::nullopt;
	}
	ListOfWords translation = vocabulary[word];
	return translation;
}

std::optional<ListOfWords> GetEnTranslation(std::string word, Vocabulary& vocabulary)
{
	ListOfWords translation;
	for (auto it = vocabulary.begin(); it != vocabulary.end(); it++)
	{
		for (auto it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			if (*it1 == word)
			{
				translation.push_back(it->first);
				return translation;
			}
		}
	}
	return std::nullopt;
}

std::optional<ListOfWords> TranslateWord(std::string word, Vocabulary& vocabulary)
{
	std::transform(word.begin(), word.end(), word.begin(), tolower);
	std::optional<ListOfWords> translation = GetRusTranslation(word, vocabulary);
	if (!translation)
	{
		translation = GetEnTranslation(word, vocabulary);
		if (!translation)
		{
			return std::nullopt;
		}
	}
	return translation;
}

void AddWord(std::string word, std::string translation, Vocabulary& vocabulary)
{
	if (IsRusWord(word))
	{
		swap(word, translation);
	}
	std::transform(word.begin(), word.end(), word.begin(), tolower);
	vocabulary[word].push_back(translation);
}
