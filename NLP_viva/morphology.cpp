#include <iostream>
#include <string.h>
#include <vector>
#include <fstream>
#include "tinyxml2.cpp"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

vector <string> segmentation(string word);
bool dictionary_Contains(string word);
void add_in_dictionary();
vector<int> get_white_spaces(string sentence);
vector<string> tokenizer(string sentence);
bool is_punctuation(char x);
void stemmer();
void segment_word(string str);
string strtrim(string sentence);
string get_data_string(string file_name);
void do_segmentation(string str, int size, string result);
void calculate_steps(string word, int size_of_word, string ans);
void print_dictionary();
vector <string> dictionary(9);
vector<string> my_vector(10);
int point = 0;
XMLDocument xml_doc;
XMLNode* root;

int main()
{
	add_in_dictionary();			
	segment_word("ilovemangoicecream");				
}



bool dictionary_Contains(string word)
{
	int p = 1;	
		
	for(int i = 0;i< dictionary.size();i++)
	{					
		if(word.compare(dictionary.at(i)) == 0)
		{			
			p = 0;			
			break;	
		}
	}
	if(p == 0) 
	{		
		return true;
	}
	else return false;
}

void add_in_dictionary()
{
	dictionary.at(0) = "i";
	dictionary.at(1) = "love";
	dictionary.at(2) = "man";
	dictionary.at(3) = "go";
	dictionary.at(4) = "mango";
	dictionary.at(5) = "how";
	dictionary.at(6) = "ice";
	dictionary.at(7) = "cream";
	dictionary.at(8) = "icecream";
}

void print_dictionary()
{	
	my_vector.at(point) = "SANJEEV";
	point ++;
	for(int i = 0;i<my_vector.size();i++)
	{
		cout<<my_vector.at(i)<<" ";
	}
}


void segment_word(string str)
{        
	cout<<str<<endl;
    do_segmentation(str, str.size(), "");
}
 
void do_segmentation(string str, int size, string result)
{       
    for (int i=1; i<=size; i++)
    {        
        string prefix = str.substr(0, i);         
        if (dictionary_Contains(prefix))
        {                
            if (i == size)
            {                
                result += prefix;
                cout << result << endl;                 
                point++;
                return;
            }
            do_segmentation(str.substr(i, size-i), size-i, result+prefix+" ");
        }
    }      
}

