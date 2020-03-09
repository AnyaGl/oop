#include "vocabulary.h"
#include <algorithm>
#include <iterator>
#include <sstream>

bool InitVocabulary(const std::string& vocabularyFileName, Vocabulary& vocabulary)
{
	std::ifstream vocabularyFile;
	vocabularyFile.open(vocabularyFileName);
	if (!vocabularyFile.is_open())
	{
		std::cout << "File could not be opened\n";
		return false;
	}
	std::string str;
	while (getline(vocabularyFile, str))
	{
		std::string enWord, ruWord;

		size_t startWord = str.find('[');
		size_t endWord = str.find(']');
		enWord = str.substr(startWord + 1, endWord - startWord - 1);
		str.erase(startWord, endWord - startWord + 2);

		endWord = str.find(',');
		while (endWord != std::string::npos)
		{
			ruWord = str.substr(0, endWord);
			str.erase(0, endWord + 2);
			vocabulary[enWord].push_back(ruWord);
			endWord = str.find(',');
		}
		vocabulary[enWord].push_back(str);
	}
	return true;
}

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

bool PrintRusTranslation(std::ostream& output, std::string word, Vocabulary& vocabulary)
{
	if (vocabulary.find(word) == vocabulary.end())
	{
		return false;
	}
	ListOfWords translation = vocabulary[word];
	for (auto it = translation.begin(); it != translation.end(); it++)
	{
		output << *it;
		if (it != translation.end() - 1)
		{
			output << ", ";
		}
	}
	output << std::endl;
	return true;
}

bool PrintEnTranslation(std::ostream& output, std::string word, Vocabulary& vocabulary)
{

	for (auto it = vocabulary.begin(); it != vocabulary.end(); it++)
	{
		for (auto it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			if (*it1 == word)
			{
				output << it->first << std::endl;
				return true;
			}
		}
	}
	return false;
}

bool PrintTranslation(std::ostream& output, std::string word, Vocabulary& vocabulary)
{
	std::transform(word.begin(), word.end(), word.begin(), tolower);
	if (!PrintRusTranslation(output, word, vocabulary))
	{
		if (!PrintEnTranslation(output, word, vocabulary))
		{
			return false;
		}
	}
	return true;
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

bool SaveVocabulary(const std::string& vocabularyFileName, const Vocabulary& vocabulary)
{
	std::ofstream output;
	output.open(vocabularyFileName);
	if (!output.is_open())
	{
		std::cout << "File to save vocabulary could not be opened\n";
		return false;
	}
	for (auto it = vocabulary.begin(); it != vocabulary.end(); it++)
	{
		output << "[" << it->first << "] ";
		for (auto it1 = it->second.begin(); it1 != it->second.end(); it1++)
		{
			output << *it1;
			if (it1 != it->second.end() - 1)
			{
				output << ", ";
			}
		}
		output << std::endl;
	}
	return true;
}
