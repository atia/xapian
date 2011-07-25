#pragma once
#include <string>
#include <list>
#include "Block.h"
#include "BinaryDictionary.h"

using namespace std;


typedef struct Word{
	int begin;
	int end;
	string value;
	int frequency;

}Word;



class FrequencyWord
{
public:
	FrequencyWord(string &input);
	~FrequencyWord();
public:
	//int *frequency;
	map<int, int> frequencyCharacters;
	string input;
	list<Block> originalBlocks;
	list<Block> potentialBlocks;
	list<string> collectedWords;
	map<string, int> potentialWords;

	list<Block> results;

	BinaryDictionary *binaryDictionary;
	void addBlock(int begin, int end);

	void collect();
	void collectPotentialWords();
	void collectFrequencyCharacters();
	void collectFrequencyWords();
	void segment();
	
};

