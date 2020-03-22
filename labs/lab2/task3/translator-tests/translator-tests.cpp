#define CATCH_CONFIG_MAIN
#include "../translator/vocabulary.h"
#include "catch2/catch.hpp"

TEST_CASE("Must be returned translation of the word")
{
	Vocabulary vocabulary = {
		{ "cat", { "кот", "кошка" } },
		{ "apple", { "яблоко" } },
		{ "ball", { "мяч" } },
		{ "the red square", { "Красная Площадь" } }
	};

	CHECK(TranslateWord("cat", vocabulary) == ListOfWords{ "кот", "кошка" });
	CHECK(TranslateWord("apple", vocabulary) == ListOfWords{ "яблоко" });
	CHECK(TranslateWord("bALl", vocabulary) == ListOfWords{ "мяч" });
	CHECK(TranslateWord("The Red Square", vocabulary) == ListOfWords{ "Красная Площадь" });
	CHECK(TranslateWord("meat", vocabulary) == std::nullopt);
}

TEST_CASE("Translations of words must be added to the vocabulary")
{
	Vocabulary vocabulary = {
		{ "cat", { "кот" } },
		{ "apple", { "яблоко" } },
		{ "ball", { "мяч" } },
		{ "the red square", { "Красная Площадь" } }
	};

	AddWord("кошка", "cat", vocabulary);
	AddWord("meat", "мясо", vocabulary);

	Vocabulary requiredVocabulary = {
		{ "cat", { "кот", "кошка" } },
		{ "apple", { "яблоко" } },
		{ "ball", { "мяч" } },
		{ "the red square", { "Красная Площадь" } },
		{ "meat", { "мясо" } }
	};

	CHECK(vocabulary == requiredVocabulary);
}
