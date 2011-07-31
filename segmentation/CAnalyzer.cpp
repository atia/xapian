#include "stdafx.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <list>
#include "PrepareDictionaries.h"

using namespace std;

#define TESTCASE(S) {#S, test_##S}
#define END_OF_TESTCASES {0, 0}

//#include "../xapian-core/tests/harness/testsuite.h"
//#include "../xapian-core/tests/harness/testutils.h"

struct test {
    const char *query;
    const char *expect;
};

/*
static const test test_or_queries[] = 
{
	{"中华人民共和国是一个不好的国家","中华人民共和国|是|一个|不好的|国家"},
	{"好漂亮的姑娘啊","好|漂亮|的|姑娘|啊"}

};

*/

void test1();
void testDoubleDictionary();

#ifndef __WIN32__
int main(int argc, char* argv[])
#else
int _tmain(int argc, _TCHAR* argv[])
#endif
{
	/*
	clock_t begin = clock();
	testDoubleDictionary();
	clock_t end = clock();
	int interval = end - begin;
	cout<<interval<<endl;
	*/
	 clock_t start = clock();
	test1();
	 clock_t finish = clock();
	int time = finish - start;
	cout<<time<<endl;
	
/*
	try {
		test_driver::parse_command_line(argc, argv);
	 return test_driver::run(tests);
	} catch (const char * e) {
		cout << e << endl;
		return 1;
	}
	*/
}





void test1()
{
	
	ifstream infile("chinese7.txt"); // the chinese1.txt is the filename to be operated
	if(!infile){
		cerr<< "unable to open file";
		return ;
	}

	string str;
	string input;
	while(infile>>str){
		input += str;
	}



//	string original = "中华人民共和国";
	string original = input;

	PrepareDictionaries * pre = new PrepareDictionaries(); 
	pre->loadHashDictionares();
	pre->createHashDictionaries();
	vector<string> output;
	pre->searchHash(original, output);
	 pre->getResult(output);

	 vector<string>::iterator iter;
	string strOutput;
	for(iter = output.begin(); iter != output.end(); iter++)
	{
		strOutput += *iter;
		strOutput += "//";
	}

	ofstream fout("4.txt");
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

	ifstream infile("chinese9.txt"); // the chinese1.txt is the filename to be operated
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
