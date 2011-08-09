// testSeg.cpp : 定义控制台应用程序的入口点。
//

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <string>
using namespace std;

#include "PrepareDictionaries.h"

#include <config.h>
#include "testsuite.h"

struct test {
    const char *query;
    const char *expect;
};


static const test test_or_queries[] = 
{
	{"chinese1.txt","result1.txt"},
	{"chinese2.txt","result2.txt"},
	{"chinese3.txt","result3.txt"},
	{"chinese4.txt","result4.txt"},	
	{"chinese5.txt","result5.txt"},
	{"chinese6.txt","result6.txt"},
	{"chinese7.txt","result7.txt"},
	{"chinese8.txt","result8.txt"},
	{"chinese9.txt","result9.txt"},
	{"chinese10.txt","result10.txt"},
	{"chinese11.txt","result11.txt"},	
	{"chinese12.txt","result12.txt"},
	{"chinese13.txt","result13.txt"},
	{"chinese14.txt","result14.txt"},
	{"chinese15.txt","result15.txt"},
	{"chinese16.txt","result16.txt"},
	{"chinese17.txt","result17.txt"},
	{"chinese18.txt","result18.txt"},
	{"chinese19.txt","result19.txt"},
	{"chinese21.txt","result20.txt"},
	{"chinese21.txt","result21.txt"},
	{"chinese22.txt","result22.txt"},	
	{"chinese23.txt","result23.txt"},
	{"chinese24.txt","result24.txt"},
	{"chinese25.txt","result25.txt"},
	{"chinese26.txt","result26.txt"},
	{"chinese27.txt","result27.txt"},
	{"chinese28.txt","result28.txt"},
	{"chinese29.txt","result29.txt"},
	{"chinese30.txt","result30.txt"},
	{"chinese31.txt","result31.txt"},
	{"chinese32.txt","result32.txt"},
	{"chinese33.txt","result33.txt"},	
	{"chinese34.txt","result34.txt"},
	{"chinese35.txt","result35.txt"},
	{"chinese36.txt","result36.txt"},
	{"chinese37.txt","result37.txt"},
	{"chinese38.txt","result38.txt"},
	{"chinese39.txt","result39.txt"},
	{"chinese40.txt","result40.txt"},
	{"chinese41.txt","result41.txt"},
	{"chinese42.txt","result42.txt"},
	{"chinese43.txt","result43.txt"},
	{"chinese44.txt","result44.txt"},
	{"chinese45.txt","result45.txt"}
	

};

string readfromFile(const char *filename)
{
	char file[30] = "testfile\\";
	
  	strcat( file, filename);
	ifstream infile(file); 
	if(!infile){
			cerr<< "unable to open file";
			return false;
	}
		
	string str;		
	string input;
	while(infile>>str){
		input += str;
	}
	infile.close();

	return input;
}

string getStringFromVector(vector<string> &output)
{
	vector<string>::iterator iter;
	string strOutput;
	for(iter = output.begin(); iter != output.end(); iter++)
	{
		strOutput += *iter;
		strOutput += "|";
	}
	return strOutput;
}


static bool test_segmentation()
{
	PrepareDictionaries * pre = new PrepareDictionaries(); 
	pre->loadHashDictionares();
	pre->createHashDictionaries();

	  
	vector<string> output;
	string input,strOutput;
	int i = 0;
	for (const test *p = test_or_queries; i < 45; i++,++p) {
		input = readfromFile(p->query);
		pre->searchHash(input);
			
		pre->getResult(output);
		
		strOutput =  getStringFromVector(output);
		
		
		TEST_STRINGS_EQUAL(strOutput, readfromFile(p->expect));
		
	}

	return true;


}


static const test_desc tests[] = {
	{"segmentation", test_segmentation}
};



int main(int argc, char* argv[])
{
	try {
		test_driver::parse_command_line(argc, argv);
		 return test_driver::run(tests);
	
	} catch (const char * e) {
		cout << e << endl;
		return 1;
	}
	
}