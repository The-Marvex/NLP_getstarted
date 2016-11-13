#include <iostream>
#include <string.h>
#include <vector>


using namespace std;

vector <string> segmentation(string word);
bool dictionary_Contains(string word);
void add_in_dictionary();
void calculate_steps(string word, int size_of_word, string ans);
void print_dictionary();

vector <string> dictionary(9);
vector<string> my_vector(10);
int point = 0;


int main()
{
	add_in_dictionary();	
	segmentation("ilovemango");
	print_dictionary();
}

vector <string> segmentation(string word)
{			
	cout<<"XX"<<word.size()<<endl;
	calculate_steps(word, word.size(), "");	
}

void calculate_steps(string word, int size_of_word, string ans)
{				
	for(int i = 1;i < size_of_word; i++)
	{					
		string sub_str = word.substr(0,i);	
		cout<<sub_str<<" ";
		if(dictionary_Contains(sub_str))
		{			
			cout<<sub_str<<" ";
			if(i == size_of_word)
			{	
				ans = ans + sub_str;
				//cout <<ans<< endl;	
				//my_vector.at(point) = ans;				
				point++;
				return;
			}	

			calculate_steps(word.substr(i, size_of_word - i),  size_of_word -i, ans+sub_str+" ");			
		}
	}
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
	cout<<"ABCD"<<endl;
	my_vector.at(point)  = "SANJEEV";
	point ++;
	for(int i = 0;i<my_vector.size();i++)
	{
		cout<<my_vector.at(i)<<" ";
	}
}