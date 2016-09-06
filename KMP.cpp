#include <iostream>
#include <string>
#include<fstream>

using namespace std;

int count_word(string data_string, string pattern_string);
int KMP_implementation(string text_string, string pattern_string);
void get_partial_match_table(string pattern_string, int pattern_len, int pmt[]);
int search_substring(string text_string, string pattern_string);
void count_paragraph(string file_name);
string get_data_string(string file_name);

int main()
{	
	string file_name, word_input, data_string, pattern_string, text_string, alpha;
	int choice, no_of_words, i, spaces, enters;	
	double probability;
	cout<<"Enter the text file name"<<endl;
	cin>>file_name;
	data_string  = get_data_string(file_name);
	cout<<data_string;
	cout<<"Enter your choice"<<endl;
	i = 0;
	while(0 == i)
	{
		cout<<"Press 1 for dictionary search"<<endl;
		cout<<"Press 2 to check KMP implementation only "<<endl;
		cout<<"Press 3 to count no of Paragraphs in the text"<<endl;
		cout<<"Press 4 to find Probability of a word in the text"<<endl;
		cout<<"Press 5 to EXIT"<<endl;
		cin>>choice;
		getline(cin, alpha);
		switch(choice)
		{
			case 1: cout<<"Enter the pattern string"<<endl;
					getline(cin, pattern_string);					
					KMP_implementation(data_string, pattern_string);
					break;
			case 2:	cout<<"Enter the text string"<<endl;
					getline(cin, text_string);
					cout<<"Enter the pattern string"<<endl;
					getline(cin, pattern_string);
					KMP_implementation(text_string, pattern_string);
					break;
			case 3:	count_paragraph(data_string);	
					break;				
			case 4:	cout<<"Enter the word"<<endl;
					cin>>word_input;
					no_of_words = count_word(data_string, word_input);
					cout<<"y fav words "<<no_of_words;
					spaces = count_word(data_string, " ");
					enters = count_word(data_string,"\n");
					enters = spaces + enters+1;
					cout<<"Total words sre: "<<enters	;				
					probability = ((no_of_words*1.00)/enters);
					cout<<"The probability is : "<<probability;		
					break;
			case 5: i =1;		
					break;					
		}
	}
}
string get_data_string(string file_name)
{
	ifstream file(file_name.c_str());
    string word;
    char x ;
    word.clear();
    int count  = 0;

    while ((x = file.get())!= EOF)
    {                          	
            word = word + x;       	        	       	                        
    }
    file.close();    
    return word;
}

int KMP_implementation(string text_string, string pattern_string)
{	int occurence = 0;	
	occurence = search_substring(text_string, pattern_string);	
	return occurence;
}

int search_substring(string text_string, string pattern_string)
{
	int pattern_len, text_len, j, i,count;
	count  = 0;
	pattern_len = pattern_string.length();
	text_len = text_string.length();	
	int pmt[pattern_len];
	j = 0;	
	get_partial_match_table(pattern_string, pattern_len, pmt);
	i = 0;
	while (i < text_len)
	{
		if (pattern_string[j] == text_string[i])
		{
			j = j+1;
			i = i+1;
		}
		if (pattern_len == j)
		{
			cout << "Pattern found at : " << (i - j) << endl;
			count = count +1;
			j = pmt[j-1];
		}
		else if ((i < text_len)&&(pattern_string[j] != text_string[i]))
		{
			if ( 0 != j)
			{
				j = pmt[j-1];
			}
			else
			{
				i = i + 1;
			}
		}
	}	
	return count;
}

void get_partial_match_table(string pattern_string, int pattern_len, int pmt[])
{
	int j = 0;
	int i = 1;
	pmt[0] = 0;	
	while (i < pattern_len)
	{
		if (pattern_string[i] == pattern_string[j])
		{
			pmt[i] = j+1;
			j++;
			i++;
		}
		else
		{
			if (0 != j)
			{
				j = pmt[j - 1];
			}
			else
			{
				pmt[i] = 0;
				i++;
			}
		}
	}
}

int count_word(string data_string, string pattern_string)
{	int times;	
	times  = KMP_implementation(data_string, pattern_string);
	return times;
}

void count_paragraph(string data_string )
{
	int enters = KMP_implementation(data_string, "\n");
	cout<<"The no of paragraphs is: "<<enters+1;	
}
