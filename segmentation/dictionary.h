#pragma once
#include <string>
#include <vector>
using namespace std;

class dictionary
{
public:
	dictionary();
public:
	virtual ~dictionary();
public:
	virtual int search(string input,int offset,int count, unsigned mapChar);
	virtual string getWord(int index);
};
