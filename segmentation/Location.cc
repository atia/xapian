#include "Location.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>
#include "unicode.h"


using namespace std;
using namespace Xapian;

Location::Location(string &input)
{
	this->input = input;
	getLocationSuffix();
	locations.clear();
}

Location::~Location()
{
}

void Location::getLocationSuffix()
{
	string str;

		
	string *locationSuffix = new string[20];
	FILE *fp;
	if((fp=fopen("location.dic","r"))==NULL)
	{
		cout<<"file not open"<<endl;
		exit(1);
	}
	int iLocation = 0;
	char aa[10];
	
	while(fgets(aa, 100, fp) != NULL)
	{
		locationSuffix[iLocation++] = string(aa, strlen(aa) - 1);
	}	

	locationDic = new BinaryDictionary(locationSuffix, iLocation);

}
	
void Location::addBlock(int begin, int end)
{
	Block block(begin, end);
	locations.push_back(block);

}
	
void Location::collectLocations(int beginIndex, int endIndex)
{	
	bool hit = false;
	int index = beginIndex;
	int begin = index;
	while(index < endIndex)
	{
		int result = locationDic->search(input, index, 1, 0);

		if(result == -1)
		{
			index = index + 3;
			continue;
		}else
		{
			index = index + result;
			addBlock(begin, index);
			begin = index;			
		}
	}
}
	