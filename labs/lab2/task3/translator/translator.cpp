#include "vocabulary.h"

void AskAndSaveChanges(const std::string& vocabularyFileName, Vocabulary& vocabulary)
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
	}
	else
	{
		std::cout << "Changes not saved. Goodbye\n";
	}
}

void RunTranslator(const std::string& vocabularyFileName, Vocabulary& vocabulary)
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
	std::string vocabularyFileName = "vocabulary.txt";
	Vocabulary vocabulary;
	if (argc == 2)
	{
		vocabularyFileName = argv[1];
		if (!InitVocabulary(vocabularyFileName, vocabulary))
		{
			std::cout << "Vocabulary is empty\n";
		}
	}

	RunTranslator(vocabularyFileName, vocabulary);

	return 0;
}
