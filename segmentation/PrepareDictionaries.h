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
#include "FrequencyWord.h"


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
	void searchHash(string &input, vector<string> &output);
	void searchDoubleHash(string input, vector<string> &output);
	string *ascWords;
	DoubleHashDictionary *dic;
	HashDictionary *dict;
	HashDictionary *familyNameDic;
	HashDictionary *titleDic;
	BinaryDictionary *numberDic;
	FrequencyWord *freWords;
	list<Block> outputList;
	list<Block> results;
	string input;

	bool hitFamily;
	int familyIndex;
	int totalNumber;
	void splitString(string input, vector<string> &list_string);
	void createHashDictionaries();
	void getFamilyNameDictionary();
	void getTitleDictionary();
	void getNumberDictionary();
	multimap<unsigned, Name> collectorNames;
	void collectNames(int beginIndex, int endIndex, vector<string> &output, int end);
	void collectChineseNumbers(int beginIndex, int endIndex, vector<string> &output, int end);
	void collectLatinWords(int beginIndex, int endIndex, vector<string> &output);
	bool isChineseDot(int offset);
	bool isLatinCharacter(char in);
	bool isNumber(char in);
	bool isPunctuate(char in);
	void collectNoFoundDictionary(int beginIndex, int endIndex);
	void addBlock(int begin, int end);
	string getResult();


};
