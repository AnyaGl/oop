#include "vocabulary.h"
#include <fstream>
#include <iostream>
#include <string>

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

bool SaveVocabulary(const std::string& vocabularyFileName, Vocabulary& vocabulary)
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

bool PrintTranslation(std::ostream& output, std::string word, Vocabulary& vocabulary)
{
	std::optional<ListOfWords> translationOpt = TranslateWord(word, vocabulary);
	if (!translationOpt)
	{
		return false;
	}
	ListOfWords translation = translationOpt.value();
	for (auto it = translation.begin(); it < translation.end(); it++)
	{
		output << *it;
		if (it != translation.end() - 1)
		{
			output << ", ";
		}
	}
	output << '\n';

	return true;
}

void AskAndSaveChanges(std::string& vocabularyFileName, Vocabulary& vocabulary)
{
	
	std::string str;
	std::cout << "The vocabulary has been modified. Enter Y or y to save before exiting\n";
	getline(std::cin, str);
	if (str == "Y" || str == "y")
	{
		if (vocabularyFileName.empty())
		{
			std::cout << "Enter file name to save\n";
			getline(std::cin, vocabularyFileName);
		}
		if (SaveVocabulary(vocabularyFileName, vocabulary))
		{
			std::cout << "Changes saved to " << vocabularyFileName << ". Goodbye\n";
		}
	}
	else
	{
		std::cout << "Changes not saved. Goodbye\n";
	}
}

void RunTranslator(std::string& vocabularyFileName, Vocabulary& vocabulary)
{
	bool vocabularyChanged = false;
	std::string word;
	while (getline(std::cin, word))
	{
		if (word == "...")
		{
			if (vocabularyChanged)
			{
				AskAndSaveChanges(vocabularyFileName, vocabulary);
			}
			break;
		}
		if (!PrintTranslation(std::cout, word, vocabulary))
		{
			std::cout << "Unknown word '" << word << "' Enter a translation or blank line to refuse.\n";
			std::string translation;
			getline(std::cin, translation);
			if (!translation.empty())
			{
				AddWord(word, translation, vocabulary);
				std::cout << "The word '" << word << "' is stored in the vocabulary as '" << translation << "'\n";
				vocabularyChanged = true;
			}
			else
			{
				std::cout << "'" << word << "' is ignored\n";
			}
		}
	}
}

int main(int argc, char* argv[])
{
	std::string vocabularyFileName;
	Vocabulary vocabulary;
	if (argc == 2)
	{
		vocabularyFileName = argv[1];
		if (!InitVocabulary(vocabularyFileName, vocabulary))
		{
			return 1;
		}
	}

	RunTranslator(vocabularyFileName, vocabulary);

	return 0;
}
