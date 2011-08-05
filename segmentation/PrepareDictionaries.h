#pragma once
#include <string>
#include <vector>
#include <map>
#include <list>
#include "Block.h"
#include "DoubleHashDictionary.h"
#include "dictionary.h"
#include "HashDictionary.h"
#include "BinaryDictionary.h"
#include "util.h"
#include "NotFoundWords.h"

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
	void searchHash(const string &original);
	void searchDoubleHash(string input, vector<string> &output);
	string *ascWords;
	DoubleHashDictionary *dic;
	HashDictionary *dict;
	
	NotFoundWords *notFoundWords;
	list<Block> outputList;
	list<Block> results;
	string input;

	bool hitFamily;
	int familyIndex;
	int totalNumber;
	void splitString(string input, vector<string> &list_string);
	void createHashDictionaries();

	multimap<unsigned, Name> collectorNames;

	
	void collectLatinWords(int beginIndex, int endIndex);
	bool isNumber(char in);
	bool isLatinCharacter(char in);
	
	bool isPunctuate(char in);
	void collectNoFoundDictionary(int beginIndex, int endIndex);
	void addBlock(int begin, int end);
	void getResult( vector<string> &output);


};
