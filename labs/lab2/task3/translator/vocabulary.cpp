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

ListOfWords GetRusTranslation(const std::string& word, const Vocabulary& vocabulary)
{
	if (auto it = vocabulary.find(word); it != vocabulary.end())
	{
		return it->second;
	}
	return {};
}

ListOfWords GetEnTranslation(const std::string& word, const Vocabulary& vocabulary)
{
	for (const auto& [enWord, ruWords] : vocabulary)
	{
		for (const auto& ruWord : ruWords)
		{
			if (ruWord == word)
			{
				return { enWord };
			}
		}
	}
	return {};
}

ListOfWords TranslateWord(std::string word, const Vocabulary& vocabulary)
{
	std::transform(word.begin(), word.end(), word.begin(), tolower);
	ListOfWords translation;
	if (translation = GetRusTranslation(word, vocabulary); !translation.empty())
	{				
		return translation;
	}
	if (translation = GetEnTranslation(word, vocabulary); !translation.empty())
	{
		return translation;
	}
	return {};
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
