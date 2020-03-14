#pragma once

#include <map>
#include <vector>
#include <optional>
#include <iterator>

typedef std::vector<std::string> ListOfWords;
typedef std::map<std::string, ListOfWords> Vocabulary;

std::optional<ListOfWords> TranslateWord(std::string word, Vocabulary& vocabulary);
void AddWord(std::string word, std::string translation, Vocabulary& vocabulary);
