#pragma once

#include <string>
#include <list>
#include "BinaryDictionary.h"
#include "Block.h"

using namespace std;

class Location
{
public:
	Location(string &input);
	~Location();
	BinaryDictionary *locationDic;
	
	string input;
	list<Block> locations;
	void getLocationSuffix();
	void addBlock(int begin, int end);
	void collectLocations(int beginIndex, int endIndex);
	
};
