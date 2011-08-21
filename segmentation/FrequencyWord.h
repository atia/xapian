#pragma once
#include <string>
#include <list>
#include <map>
#include "Block.h"
#include "BinaryDictionary.h"

using namespace std;






class FrequencyWord
{
public:
	FrequencyWord(string &input, list<Block> &orginalBlocksS);
	~FrequencyWord();
public:
	map<int, int> frequencyCharacters;
	string input;
	list<Block> originalBlocks;
	list<Block> potentialBlocks;
	list<string> collectedWords;
	map<string, int> potentialWords;

	list<Block> results;

	BinaryDictionary *binaryDictionary;
	void analyzeBlocks();

	void collect();
	void collectPotentialWords();
	void collectFrequencyCharacters();
	void collectFrequencyWords();
	void segment();
	
};

