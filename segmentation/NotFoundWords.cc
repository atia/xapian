#include "StdAfx.h"
#include "NotFoundWords.h"
#include "FrequencyWord.h"

NotFoundWords::NotFoundWords(string &input)
{
	this->input = input;
	results.clear();
	nnResults.clear();
	frequnceyWords.clear();
	
	originalBlocks.clear();
}

NotFoundWords::~NotFoundWords(void)
{
}


void NotFoundWords::addBlock(int begin, int end)
{
	Block block(begin, end);
	originalBlocks.push_back(block);
}

void NotFoundWords::collect()
{
	collectFrequencyWords();	
	collectOtherWords();
}


void NotFoundWords::collectFrequencyWords()
{
	FrequencyWord *freWords = new FrequencyWord(input, originalBlocks);
	freWords->analyzeBlocks();
	frequnceyWords = freWords->results;	
}

void NotFoundWords::collectOtherWords()
{
	chNumbers = new ChineseNumbers(input);
	chNames = new ChineseNames(input);
	std::list<Block>::iterator iterOriginal;
	iterFrequency = frequnceyWords.begin();
	string temp;
	Block block;
	for (iterOriginal=originalBlocks.begin();   iterOriginal!=originalBlocks.end();   ++iterOriginal) 
	{
		block = *iterOriginal;
		collectWords(block.begin, block.end);
		
	}

	analyzerNamesandNumbersResults();
	getFinalResults();
}

void NotFoundWords::collectWords(int begin, int end)
{
	if(iterFrequency == frequnceyWords.end())
	{
	
		chNumbers->collectChineseNumbers(begin, end);
		chNames->collectNames(begin, end);		
	
	}else
	{

		Block block = *iterFrequency;
		if(block.begin >= begin && block.end <= end)
		{
			collectWords(begin, block.begin);
			collectWords(block.end, end);
			iterFrequency++;
		}else if(block.begin >= begin && block.begin < end && block.end >= end)
		{
			collectWords(begin, block.begin);
		}else if(block.begin < begin && block.end > begin && block.end < end)
		{
			collectWords(block.end, end);
			iterFrequency++;
		}else
		{
			chNumbers->collectChineseNumbers(begin, end);
			chNames->collectNames(begin, end);		
		}
	}

}

void NotFoundWords::analyzerNamesandNumbersResults()
{
	Block block1, block2;
	std::list<Block>::iterator iter1 = chNumbers->chineseNumbers.begin();
	std::list<Block>::iterator iter2 = chNames->names.begin();
	while((iter1 != chNumbers->chineseNumbers.end()) && (iter2 != chNames->names.end()))
	{
		block1 = *iter1;
		block2 = *iter2;
		if(block1.begin > block2.begin)
		{
			nnResults.push_back(block2);
			iter2++;
		}
		else if(block1.begin < block2.begin)
		{
			nnResults.push_back(block1);
			iter1++;

		}else
		{
			if(block1.end == block2.end)
			{
				nnResults.push_back(block1);
				iter1++;
				iter2++;
			}
			else if(block1.end < block2.end)
			{
				nnResults.push_back(block1);
				iter1++;
			}else
			{
				nnResults.push_back(block2);
				iter2++;
			}
		}

	}
	
	while(iter1 != chNumbers->chineseNumbers.end())
	{
		block1 = *iter1;
		nnResults.push_back(block1);
		*iter1++;
	}
	while(iter2 !=chNames->names.end())
	{
		block2 = *iter2;
		nnResults.push_back(block2);
		*iter2++;
	}

}


void NotFoundWords::getFinalResults()
{
	Block block1, block2;
	std::list<Block>::iterator iter1 = frequnceyWords.begin();
	std::list<Block>::iterator iter2 = nnResults.begin();
	while((iter1 != frequnceyWords.end()) && (iter2 != nnResults.end()))
	{
		block1 = *iter1;
		block2 = *iter2;
		if(block1.begin > block2.begin)
		{
			results.push_back(block2);
			iter2++;
		}
		else if(block1.begin < block2.begin)
		{
			results.push_back(block1);
			iter1++;

		}else
		{
			if(block1.end == block2.end)
			{
				results.push_back(block1);
				iter1++;
				iter2++;
			}
			else if(block1.end < block2.end)
			{
				results.push_back(block1);
				iter1++;
			}else
			{
				results.push_back(block2);
				iter2++;
			}
		}

	}
	
	while(iter1 != frequnceyWords.end())
	{
		block1 = *iter1;
		results.push_back(block1);
		*iter1++;
	}
	while(iter2 !=nnResults.end())
	{
		block2 = *iter2;
		results.push_back(block2);
		*iter2++;
	}
}


