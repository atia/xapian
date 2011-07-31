#pragma once

#include <list>
#include <string>
#include "BinaryDictionary.h"
#include "Block.h"
using namespace std;

class ChineseNumbers
{
public:
	ChineseNumbers(string &input);
	~ChineseNumbers();
	string input;
	BinaryDictionary *numberDic;
	void getNumberDictionary();
	void collectChineseNumbers(int beginIndex, int endIndex);
	bool isNumber(char in);
	bool isChineseDot(int offset);
	void addBlock(int begin, int end);
	list<Block> chineseNumbers;
};
