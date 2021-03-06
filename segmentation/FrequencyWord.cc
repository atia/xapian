#include "StdAfx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include "FrequencyWord.h"
#include "unicode.h"


using namespace std;
using namespace Xapian;

int frequency[22000];

FrequencyWord::FrequencyWord(string &input, list<Block> &orginalBlocks)
{
	this->input = input;
	this->originalBlocks = orginalBlocks;
	analyzeBlocks();
	originalBlocks.clear();
	potentialBlocks.clear();
	collectedWords.clear();
	potentialWords.clear();

	results.clear();
	
}

FrequencyWord::~FrequencyWord()
{
	
}



void FrequencyWord::analyzeBlocks()
{
	std::list<Block>::iterator iter;
	string temp;
	Block block;
	for (iter=originalBlocks.begin();   iter!=originalBlocks.end();   ++iter) 
	{
		block = *iter;
		//temp = input.substr(block.begin, block.end - block.begin);
		string temp(input, block.begin, block.end - block.begin);
		Utf8Iterator it(temp);
		int character;
		while(it !=Utf8Iterator())
		{

			character = *it;
			if(character <= 40895 && character >= 19968)
			{
				frequency[character - 19968]++;
			}
			++it;
		}
	}

	collect();
}

void FrequencyWord::collect()
{
	 collectFrequencyCharacters();
	 collectPotentialWords();	
	 collectFrequencyWords();
	 segment();
}

bool comp(const string& str1, const string& str2)
{
	return str1.compare(str2) < 0;
}


void FrequencyWord::collectFrequencyCharacters()
{	
	for(int i = 0; i < 22000; i++)
	{
		if(frequency[i] > 2)
			frequencyCharacters.insert(pair<int,int>(i + 19968,frequency[i]));
	}
}


void FrequencyWord::collectPotentialWords()
{
	list<Block>::iterator it;
	
	Block tempBlock;
	string output;

	for (it=originalBlocks.begin();   it!=originalBlocks.end();   ++it) 
	{ 
		tempBlock = *it;
		string strTemp = input.substr(tempBlock.begin, tempBlock.end - tempBlock.begin);
		Utf8Iterator utf(strTemp);
		int beginIndex = tempBlock.begin;
		int index = beginIndex;
		unsigned character;
		bool hit = false;
	
		while(utf !=Utf8Iterator())
		{

			character = *utf;
			std::map<int,int>::iterator m = frequencyCharacters.find(character);
			if(m != frequencyCharacters.end())
			{
				hit = true;
			}
			beginIndex = index;
			++utf;
			index+= 3;

			while(hit &&utf !=Utf8Iterator())
			{
			
				character = *utf;
			
				std::map<int,int>::iterator m = frequencyCharacters.find(character);
				if(m != frequencyCharacters.end())
				{
					hit = true;
				}
				else
				{
					hit = false;
				}
				++utf;
				index+= 3;

			}

			if(index - beginIndex >= 6)
			{
				Block block(beginIndex, index); 
				potentialBlocks.push_back(block);
				collectedWords.push_back(input.substr(beginIndex, index - beginIndex));	
			
			}
		
		}
	}

	
}


void FrequencyWord::collectFrequencyWords()
{
	
	collectedWords.sort(comp);
	vector<string> tempWords;
	string temp, potentialWord;
	int count = 0;
	list<string>::const_iterator citer = collectedWords.begin(); 
	while(citer != collectedWords.end())//looking for potential words;
	{
		count = 1;
		potentialWord = temp = *citer;
		++citer;
		while(temp.compare(potentialWord) == 0 &&citer != collectedWords.end())
		{
			count++;		
			temp = *citer;

			++citer;
		}
		if(count>2)
			tempWords.push_back(potentialWord);

	}
	
	int size = tempWords.size();
	string *tempDictionary = new string[size];
	copy(tempWords.begin(), tempWords.end(), tempDictionary);

	//make binaryDictionary
	binaryDictionary = new BinaryDictionary(tempDictionary, size);

}

void FrequencyWord::segment()
{
	//segment the string using word not in dictionary
	Block block;
	list<Block>::iterator it;
	for(it=potentialBlocks.begin();   it!=potentialBlocks.end();   ++it) 
	{
		block = *it;
		int begin = block.begin;
		int index = block.begin;
		while(index < block.end)
		{
			int result = binaryDictionary->search(input, index, 1, 0);
			if(result > 0)
			{
				Block tempBlock(index, index + result);
				results.push_back(tempBlock);
				index += result;
			}else
			{
				index += 3;
			}
			
		}
		
	}


}