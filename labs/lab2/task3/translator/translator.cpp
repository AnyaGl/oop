#include "vocabulary.h"
#include <fstream>
#include <iostream>
#include <string>

ListOfWords Split(std::string str, const std::string& delimiter)
{
	ListOfWords splitStrings;
	std::string substring;
	size_t endFind = str.find(delimiter);
	while (endFind != std::string::npos)
	{
		substring = str.substr(0, endFind);
		str.erase(0, endFind + delimiter.length());
		splitStrings.push_back(substring);
		endFind = str.find(delimiter);
	}
	splitStrings.push_back(str);
	return splitStrings;
}

bool InitVocabulary(const std::string& vocabularyFileName, Vocabulary& vocabulary)
{
	vocabulary = {};
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
		size_t startWord = str.find('[');
		size_t lenWord = str.find(']') - startWord - 1;
		std::string enWord = str.substr(startWord + 1, lenWord);
		str.erase(startWord, lenWord + 3);

		vocabulary[enWord] = Split(str, ", ");
	}
	return true;
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
	for (const auto& [enWord, ruWords] : vocabulary)
	{
		output << "[" << enWord << "] ";
		for (auto it = ruWords.begin(); it != ruWords.end(); it++)
		{
			output << *it;
			if (it != ruWords.end() - 1)
			{
				output << ", ";
			}
		}
		output << std::endl;
	}
	return true;
}

bool PrintTranslation(std::ostream& output, const std::string& word, const Vocabulary& vocabulary)
{
	ListOfWords translation = TranslateWord(word, vocabulary);
	if (translation.empty())
	{
		return false;
	}
	for (auto it = translation.begin(); it != translation.end(); it++)
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

void AskAndSaveChanges(const std::string& vocabularyFileName, const Vocabulary& vocabulary)
{
	std::string str;
	std::cout << "The vocabulary has been modified. Enter Y or y to save before exiting\n";
	getline(std::cin, str);
	if (str == "Y" || str == "y")
	{
		if (SaveVocabulary(vocabularyFileName, vocabulary))
		{
			std::cout << "Changes saved to " << vocabularyFileName << ". Goodbye\n";
		}
		else
		{
			std::cout << "Vocabulary could not be saved. Goodbye\n";
		}
	}
	else
	{
		std::cout << "Changes not saved. Goodbye\n";
	}
}

void RunTranslator(Vocabulary& vocabulary, bool& vocabularyChanged)
{
	vocabularyChanged = false;
	std::string word;
	while (getline(std::cin, word))
	{
		if (word == "...")
		{
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
	else if (argc > 2)
	{
		std::cout << "Invalid number of arguments\n";
		std::cout << "Usage: translator.exe [<vocabulary file>]\n";
		return 1;
	}

	bool vocabularyChanged = false;
	RunTranslator(vocabulary, vocabularyChanged);

	if (vocabularyChanged)
	{
		if (vocabularyFileName.empty())
		{
			std::cout << "Enter file name to save\n";
			getline(std::cin, vocabularyFileName);
		}
		AskAndSaveChanges(vocabularyFileName, vocabulary);
	}

	return 0;
}
