#pragma once
#include <string>
#include <vector>
#include <map>
#include <list>
#include "Block.h"

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
	string *ascWords;
	
	HashDictionary *dict;
	
	NotFoundWords *notFoundWords;
	list<Block> outputList;
	list<Block> results;
	string input;

	int totalNumber;
	
	void collectLatinWords(int beginIndex, int endIndex);
	bool isNumber(char in);
	bool isLatinCharacter(char in);
	
	bool isPunctuate(char in);
	void collectNoFoundDictionary(int beginIndex, int endIndex);
	void addBlock(int begin, int end);
	void getResult( vector<string> &output);
	void twoSplit(int beginIndex, int endIndex, vector<string> &output);


};
