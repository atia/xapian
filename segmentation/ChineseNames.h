#pragma once

#include <string>
#include <list>
#include "HashDictionary.h"
#include "Block.h"

using namespace std;

class ChineseNames
{
public:
	ChineseNames(string &input);
	~ChineseNames();

	HashDictionary *familyNameDic;
	HashDictionary *titleDic;
		
	string input;
	list<Block> names;
	void getFamilyNameDictionary();
	void getTitleDictionary();
	void addBlock(int begin, int end);
	void collectNames(int beginIndex, int endIndex);
	
};
