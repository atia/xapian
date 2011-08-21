#include "StdAfx.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "unicode.h"


using namespace std;
using namespace Xapian;

#include "ChineseNumbers.h"

ChineseNumbers::ChineseNumbers(string &input)
{
	this->input = input;
	getNumberDictionary();
}

ChineseNumbers::~ChineseNumbers()
{
}


void ChineseNumbers::getNumberDictionary()
{
	string str;		
	string *numbers = new string[30];
	FILE *fp;
	if((fp=fopen("number.dic","r"))==NULL)
	{
		cout<<"file not open"<<endl;
		exit(1);
	}
	int index = 0;
	char aa[10];
	
	while(fgets(aa, 10, fp) != NULL)
	{
		numbers[index++] = string(aa, strlen(aa) - 1);
	}	

	numberDic = new BinaryDictionary(numbers, index);
}

bool ChineseNumbers::isChineseDot(int offset)
{
	string str = input.substr(offset, 3);
	Utf8Iterator it(str);
	unsigned temp = *it;
	if(temp == 28857)
		return true;
	else
		return false;
}


void ChineseNumbers::collectChineseNumbers(int beginIndex, int endIndex)
{
	bool hit = false;
	
	int index = beginIndex;
	bool result;
	int begin = beginIndex;
	int falseBegin = beginIndex;
	unsigned temp;
	bool dot = false; //one Chinese number should only contain only one dot
	string str;
	while(index < endIndex)
	{
		result = numberDic->search(input, index); //check whether the next character is a Chinese-number character
		if(result) // if it is a Chinese character
		{
			if(hit == false)
			{
				hit = true;
				begin = index;
				if(begin > falseBegin)
				{
					addBlock(falseBegin, begin);
					falseBegin= index;
				}
			}
			index += 3;
		}else
		{
			if(dot)
			{
				hit = false;
				index += 3;
			}

			if(hit)
			{
				dot = isChineseDot(index);
				if (dot) 
				{
					result = numberDic->search(input, index + 3);
					if(result == true)
						index += 6;
					else
					{
						
							if(begin == beginIndex) // if the numbers are in first location, then check the characters before it
							{
								while(hit)
								{
									begin -= 3;
									result = numberDic->search(input, begin);
									if(!result)
									{
										if(dot)
										{
											hit = false;
										}
										else
										{
											dot = isChineseDot(begin);
											if(!dot)
												hit = false;

										}

									}
								}
							}
						
						
						addBlock(begin, index);
						hit = false;
						falseBegin = index;
						index += 6;
					}
				}
				else
				{
					
					addBlock(begin, index);
					hit = false;
					falseBegin = index;
					index += 3;
				}
			}
			else
				index += 3;
		}

	}


	if(hit == true){ // if the string which is not found in dictionary is finished, then search the string followed
					//because some numbers will be in dictionary as other meaning, and it will be segement before collect numbers
					// so we have to search the followed characters.

		while(hit)
		{
			result = numberDic->search(input, index);
			if(!result)
			{
				if(dot)
					hit = false;
				else{
					dot = isChineseDot(index);
					if(!dot)
						hit = false;

				}
			}
			index += 3;
		}

		
		index -= 6;
		result = numberDic->search(input, index);

		if(result)
			index += 3;



		hit = true;
		
		if(begin == beginIndex) // if the numbers are in first location, then check the characters before it
		{
			while(hit)
			{
				begin -= 3;
				result = numberDic->search(input, begin);
				if(!result)
				{
					if(dot)
					{
						hit = false;
					}
					else
					{
						dot = isChineseDot(begin);
						if(!dot)
							hit = false;
					}
				}
			}
		}
		
		begin += 3;


	
		addBlock(begin, index);
	}
	else
	{
		
		addBlock(falseBegin, endIndex);
	}

}


void ChineseNumbers::addBlock(int begin, int end)
{
	Block block(begin, end);
	if(!chineseNumbers.empty())
	{
		Block laterBlock = chineseNumbers.back();
		if(block.begin >= laterBlock.begin && block.end <= laterBlock.end)
			return;
	}
	
	if((end - begin) == 3) //if the number is just a single number, do not deal it
		return;

	chineseNumbers.push_back(block);
	
}