#pragma once
#include <string>
#include <vector>
#include <map>
#include "DoubleHashDictionary.h"
#include "dictionary.h"
#include "HashDictionary.h"
#include "util.h"

using namespace std;


class PrepareDictionaries
{
public:
	PrepareDictionaries();
public:
	~PrepareDictionaries();

	
	void loadDictionares();
	void loadHashDictionares();
	void createDoubleHashDictionries();
	void searchHash(string input, vector<string> &output);
	void searchDoubleHash(string input, vector<string> &output);
	string *ascWords;
	DoubleHashDictionary *dic;
	HashDictionary *dict;
	HashDictionary *familyNameDic;
	HashDictionary *titleDic;
	bool hitFamily;
	int familyIndex;
	int totalNumber;
	void splitString(string input, vector<string> &list_string);
	void createHashDictionaries();
	void getFamilyNameDictionary();
	void getTitleDictionary();
	multimap<unsigned, Name> collectorNames;
	void collectNames(string input, int beginIndex, int endIndex, vector<string> &output, int end);
};
