#pragma once

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

typedef std::vector<std::string> ListOfWords;
typedef std::map<std::string, ListOfWords> Vocabulary;

bool InitVocabulary(const std::string& vocabularyFileName, Vocabulary& vocabulary);
bool PrintTranslation(std::ostream& output, std::string word, Vocabulary& vocabulary);
void AddWord(std::string word, std::string translation, Vocabulary& vocabulary);
bool SaveVocabulary(const std::string& vocabularyFileName, Vocabulary& vocabulary);
