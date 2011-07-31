#include "StdAfx.h"
#include "ChineseNames.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "unicode.h"


using namespace std;
using namespace Xapian;

ChineseNames::ChineseNames(string &input)
{
	this->input = input;
	getFamilyNameDictionary();
	getTitleDictionary();
}

ChineseNames::~ChineseNames()
{
}

void ChineseNames::getFamilyNameDictionary()
{
	string str;

		
	string *familyNames = new string[500];
	FILE *fp;
	if((fp=fopen("x-confucian-family-name.dic","r"))==NULL)
	{
		cout<<"file not open"<<endl;
		exit(1);
	}
	int iFamily = 0;
	char aa[100];
	
	while(fgets(aa, 100, fp) != NULL)
	{
		familyNames[iFamily++] = string(aa, strlen(aa) - 1);
	}	

	familyNameDic = new HashDictionary(familyNames, iFamily);

}

void ChineseNames::getTitleDictionary()
{
	string str;		
	string *titleWords = new string[500];
	FILE *fp;
	if((fp=fopen("title.dic","r"))==NULL)
	{
		cout<<"file not open"<<endl;
		exit(1);
	}
	int index = 0;
	char aa[100];
	
	while(fgets(aa, 100, fp) != NULL)
	{
		titleWords[index++] = string(aa, strlen(aa) - 1);
	}	

	titleDic = new HashDictionary(titleWords, index);

}



void ChineseNames::collectNames(int beginIndex, int endIndex)
{
	bool hit = false;
	int index = beginIndex;
	while(index < endIndex)
	{
		int result = familyNameDic->search(input, index, 1, 0);
		if(result == -1)
		{
			if(hit == true)
			{
				hit = false;
				beginIndex = index;
			}
			index += 3;
		}
		else 
		{
			if(hit == false)
			{
				hit = true;
				addBlock(beginIndex, index);
				
			}

			if(result == 6) 
			{
				addBlock(index, index + result);
				
			}

			//check whether it followed by a title
			int titleResult = titleDic->search(input, index + result, 1, 0);
			if(titleResult > 0) //if a family name followed by a title , it can be recognized be a name
			{
				addBlock(index, index + result + titleResult);
				index += result + titleResult;
			}
			else
			{		
				// if there is a character between a family name and a title, then the character between them might be a first name
				titleResult = titleDic->search(input, index + result + 3, 1, 0);
				if(titleResult > 0)
				{
					addBlock(index, index + result + 3);
					addBlock(index, index + result + 3 + titleResult);
					index += result + 3 + titleResult;
				}else
				{
					//check whether there are two characters between a family name and a title.
					titleResult = titleDic->search(input, index +  result + 6, 1, 0);
					if(titleResult > 0)
					{
						addBlock(index, index + result + 6 + titleResult);
						index +=  result + 6 + titleResult;
					}
					else
					{
						//if there is not a title found			
						int left = endIndex - index - result; 
						if(left > 6)
						{
							addBlock(index, index + result + 3);
							addBlock(index, index + result + 6);
						}
						if(left ==  0)
						{
							return;
						}else if(left == 3)
						{
							addBlock(index, index + result + 3);
							return;
						}
						else if(left == 6)
						{
							addBlock(index, index + result + 3);
							addBlock(index, index + result + 6);
							
							addBlock(index + result, index + result + 6);
							return;
						}else{
							index += result;
						}
					}

				}

			}
				
		}
	}
	if(hit == false)
	{
		addBlock(beginIndex, index);
	}
	
}

void ChineseNames::addBlock(int begin, int end)
{
	Block block(begin, end);
	names.push_back(block);
	
}