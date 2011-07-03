#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include "PrepareDictionaries.h"

using namespace std;

void test1();
void testDoubleDictionary();

int _tmain(int argc, _TCHAR* argv[])
{
	
	test1();
	
}


void test1()
{
	
	ifstream infile("chinese6.txt"); // the chinese1.txt is the filename to be operated
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}

	string str;
	string input;
	while(infile>>str){
		input += str;
	}

	PrepareDictionaries * pre = new PrepareDictionaries(); 
	pre->loadHashDictionares();
	pre->createHashDictionaries();
	vector<string> output;
	pre->searchHash(input, output);
	

	vector<string>::iterator iter;
	string strOutput;
	for(iter = output.begin(); iter != output.end(); iter++)
	{
		strOutput += *iter;
		strOutput += "//";
	}

	ofstream fout("3.txt");
    if(!fout)
    {
        fout << "Cannot open output file\n";
        return ;
    } 

	fout<<strOutput;
	fout.close();

	

}


void testDoubleDictionary()
{

	ifstream infile("chinese2.txt"); // the chinese1.txt is the filename to be operated
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}

	string str;
	string input;
	while(infile>>str){
		input += str;
	}

	PrepareDictionaries * pre = new PrepareDictionaries(); 
	pre->loadDictionares();
	pre->createDoubleHashDictionries();
	vector<string> output;
	pre->searchDoubleHash(input,output);

	vector<string>::iterator iter;
	string strOutput;
	for(iter = output.begin(); iter != output.end(); iter++)
	{
		strOutput += *iter;
		strOutput += "//";
	}

	ofstream fout("3.txt");
    if(!fout)
    {
        fout << "Cannot open output file\n";
        return ;
    } 

	fout<<strOutput;
	fout.close();
}