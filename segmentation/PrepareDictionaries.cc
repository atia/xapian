#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <map>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <list>
#include <time.h>
#include "HashDictionary.h"
#include "PrepareDictionaries.h"
#include "HashDictionary.h"
#include "DoubleHashDictionary.h"
#include "BinaryDictionary.h"
#include "unicode.h"


using namespace std;
using namespace Xapian;

PrepareDictionaries::PrepareDictionaries()
{
	
}

PrepareDictionaries::~PrepareDictionaries()
{
}


void PrepareDictionaries::loadDictionares()
{
	
	string str;		
	ascWords = new string[230000];
	FILE *fp;
	if((fp=fopen("compiled-base.dic","r"))==NULL)
	{
		cout<<"file not open"<<endl;
		exit(1);
	}
	totalNumber = 0;
	char aa[100];
	fgets(aa, 100, fp);
	
	string temp = string(aa, strlen(aa) - 1);

	ascWords[totalNumber++] = temp.substr(3);
	
	
	while(fgets(aa, 100, fp) != NULL)
	{
		ascWords[totalNumber++] = string(aa, strlen(aa) - 1);
	}	
	dic = new DoubleHashDictionary(ascWords, totalNumber);
		
}


void PrepareDictionaries::loadHashDictionares()
{
	
	string str;
		
	ascWords = new string[230000];
	FILE *fp;
	if((fp=fopen("t-base.dic","r"))==NULL)
	{
		cout<<"file not open"<<endl;
		exit(1);
	}
	totalNumber = 0;
	char aa[100];
	
	while(fgets(aa, 100, fp) != NULL)
	{
		ascWords[totalNumber++] = string(aa, strlen(aa) - 1);
	}	

	dict = new HashDictionary(ascWords, totalNumber);	
	
}



void PrepareDictionaries:: searchDoubleHash(string input, vector<string> &output)
{
	dic->search(input, output);
}

void PrepareDictionaries::searchHash(const string &original)
{
	outputList.clear();
	results.clear();
	input = original;
	notFoundWords = new NotFoundWords(input);

 	int offset = 0, index = 0;
	size_t inputLength = input.size();

	bool hit = false;
	

	int beginIndex = 0;
	int end = 0;
	int begin = 0;
	unsigned temp = 0;
	size_t leftLength;	
	Utf8Iterator it(input);
	
	
	while(offset < inputLength)  //characters before offset is already segmented
	{
		//looking for a begin for a Chinese substring
		while(it != Utf8Iterator()) 
		{
			temp = *it;
			
			if( temp >= 19968 && temp <= 40895) //0x4E00 = 19968 Ox9FBF = 40895
			{
				begin = inputLength - it.left();		
				break;
			}
			++it;
		}	
		
		
		//deal with none Chinese characters
		collectLatinWords(offset, begin);
	
	

		//looking for a end for a Chinese substring
		while(it != Utf8Iterator()) 
		{
 			temp = *it;
			if(temp < 19968 || temp > 40895)
			{
				end = inputLength - it.left();		
				break;
			}
			++it;
		}

		if(it == Utf8Iterator())
			end = inputLength;

		beginIndex = begin;
		while(begin < end)
		{
			
			int result = dict->search(input,begin,1,end);
			if(result == -1)
			{
				
				if(hit == true)
				{
					hit = false;
					beginIndex = begin;
				}		
				
				begin=begin+3;
			}
			else
			{
				
				if(hit == false)
				{
					hit = true;						
					collectNoFoundDictionary(beginIndex, begin);
				}

 				
				addBlock(begin, begin + result);
				begin += result;
				
			}
		}
		if(hit == false)
		{
			hit = true;
		
			addBlock(beginIndex, end);
			
		}

		offset = end;
	}

	notFoundWords->collect();
	
}


void PrepareDictionaries::collectNoFoundDictionary(int beginIndex, int endIndex)
{
	if(endIndex - beginIndex >= 6)
		notFoundWords->addBlock(beginIndex,endIndex);

}

void PrepareDictionaries::collectLatinWords(int beginIndex, int endIndex)
{
	char temp;
	int index = beginIndex;
	bool hit = false;
	int dot = -1;
	int begin = beginIndex;
	int falseBegin = beginIndex;
	while(index < endIndex)
	{
		temp = input[index];
		if(isLatinCharacter(temp))
		{
			begin = index;
			if(!hit)
			{
				
				addBlock(falseBegin, index);
			}			
			hit = true;
			while(hit)
			{
				index++;
				temp = input[index];
				if(!isLatinCharacter(temp))
					hit = false;
			}
			
			addBlock(begin, index);
			hit = true;
		}
		else if(isNumber(temp))
		{
			
			begin = index;
			if(!hit)
			{
			
				addBlock(falseBegin, index);
			}
			hit = true;
			index++;
			while(hit)
			{
				temp = input[index];
				
				if(isNumber(temp)||isPunctuate(temp))
				{
					index++;
				}
				else 
				{
					hit = false;
				}

					
			}		
		
			addBlock(begin, index);
			hit = true;
			
		}else
		{
			if(hit)
			{
				hit = false;
				falseBegin = index;
			}
			index++;
		}
	}
	
	
}


bool PrepareDictionaries::isPunctuate(char in)
{
	if(in == '-' || in == '/' || in== ',' || in == '.') // these are the possible character in Numbers
		return true;
	else
		return false;
}

bool PrepareDictionaries::isNumber(char in)
{
	if(in >= '0' && in <= '9')
		return true;
	else
		return false;
}
	
bool PrepareDictionaries::isLatinCharacter(char in)
{
	if((in >= 'a' && in <= 'z')
		|| (in >= 'A' && in <= 'Z'))
		return true;
	else
		return false;
}



void PrepareDictionaries::addBlock(int begin, int end)
{
	Block block(begin, end);
	outputList.push_back(block);
	
}

void PrepareDictionaries::getResult( vector<string> &output)
{
	output.clear();	
	Block block1, block2;
	std::list<Block>::iterator iter1 = notFoundWords->results.begin();
	std::list<Block>::iterator iter2 = outputList.begin();
	while((iter1 != notFoundWords->results.end()) && (iter2 != outputList.end()))
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
	
	while(iter1 != notFoundWords->results.end())
	{
		block1 = *iter1;
		results.push_back(block1);
		*iter1++;
	}
	while(iter2 !=outputList.end())
	{
		block2 = *iter2;
		results.push_back(block2);
		*iter2++;
	}

	std::list<Block>::iterator iter;
	Block block;
	string temp;
	
	int begin = 0;
	int end = 0;

	for(iter = results.begin(); iter != results.end(); iter++)
	{
 		block = *iter;
		if(block.begin > end)
		{			
			temp = input.substr(end, block.begin - end);
			output.push_back(temp);
			twoSplit(end, block.begin, output);
		}
		if(block.begin == block.end)
			continue;
		temp = input.substr(block.begin, block.end - block.begin);
		output.push_back(temp);
		end = block.end;
	}
	
}



void PrepareDictionaries::twoSplit(int beginIndex, int endIndex, vector<string> &output)
{
	//twoSplit 
	//if the string is ABC,then get AB/BC
	//if the string is ABCD, then get AB/BC/CD,and so on
	if((endIndex - beginIndex) < 9)
		return;
	else
	{
		int index = beginIndex;
		while((endIndex - index) >=6)
		{
			output.push_back(input.substr(index, 6));
			index += 3;
		}
	}

}



void PrepareDictionaries::splitString(string input, vector<string> &list_string)
{


}


void PrepareDictionaries::createHashDictionaries()
{

	//dic  = new HashDictionary(ascWords, totalNumber);
	
}

void PrepareDictionaries::createDoubleHashDictionries()
{
}
