#pragma once
#include <list>
#include <string>
#include "Block.h"
#include "ChineseNumbers.h"
#include "ChineseNames.h"
#include "Location.h"
using namespace std;


class NotFoundWords
{
public:
	NotFoundWords(string &input);
	~NotFoundWords();
	string input;
	ChineseNumbers *chNumbers;
	ChineseNames *chNames;
	Location *locations;
	list<Block> results;
	list<Block> nnResults;
	list<Block> frequnceyWords;
	std::list<Block>::iterator iterFrequency;
	list<Block> originalBlocks;
	void addBlock(int begin, int end);
	void collect();
	void collectFrequencyWords();
	void collectOtherWords();
	void collectWords(int begin, int end);
	void analyzerNamesandNumbersResults();
	void getFinalResults();
	
};
