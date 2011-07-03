#define NOMINMAX
#include "StdAfx.h"
#include <algorithm>
#include "BinaryDictionary.h"


BinaryDictionary::BinaryDictionary(string *ascWords, int count)
{
	this->ascWords = ascWords;
	this->beginIndex = 0;
	this->endIndex = count;
	this->count = count;
	this->hit = false;
}

BinaryDictionary::~BinaryDictionary()
{
}


BinaryDictionary::BinaryDictionary(std::string *ascWords, int beginIndex, int endIndex, int totalCount)
{
	this->ascWords = ascWords;
	this->beginIndex = beginIndex;
	this->endIndex = endIndex;
	this->count = endIndex - beginIndex;
	this->hit = false;

}

BinaryDictionary::BinaryDictionary(charArray *ascWords, int beginIndex, int endIndex, int totalCount)
{
	this->ascInputs = ascWords;
	this->beginIndex = beginIndex;
	this->endIndex = endIndex;
	this->count = endIndex - beginIndex;
	this->hit = false;

}

string BinaryDictionary::getWord(int index)
{
	return ascWords[beginIndex + index];
}



int BinaryDictionary::size()
{
	return count;
}



int BinaryDictionary::search(string input,int offset,int count, unsigned mapChar){ 
	
	hit = false;
	string temp = input.substr(offset, count * 3);
	temp +='\n';
	int searchResult = search(temp);
	int index = searchResult;
	int resultlength = -1;
	if(hit == true)
	{
		index++;
		resultlength = count * 3;
		
	}
	size_t maxLength = count * 3;
	
	for(;index<endIndex;index++)
	{
		size_t length = ascWords[index].size();
		if( length < maxLength)
			break;
		if((input.size() - offset) < length)
			break;
		maxLength = length;
		if(input.compare(offset,length, ascWords[index]) == 0)
		{
			hit = true;
			resultlength = length;			
		}	
	}
	return resultlength;
	
}



int BinaryDictionary::search(string str) //check whether str in the array,using binary search
{
	int begin = beginIndex;
	int end = endIndex;
	int result;
	int middle;
	while(begin <= end)
	{
		middle = (begin + end) / 2;
		string temp = ascWords[middle];
		result = compare(str, ascWords[middle]);
		if(result == 0)
		{
			hit = true;
			return middle;
		}
		else if(result > 0)
		{
			begin =middle + 1;
		}else
		{
			end = middle - 1;
		}
		
	}
	return end;
}

int BinaryDictionary::compare(std::string str1, std::string str2)
{
	return str1.compare(str2);
	
}