#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>

using namespace std;

void count_words();
void count_lines();
string getdata_string();
vector<string> tokenize_sentence(string sentence);
vector<int> KMP_implementation(string text_string, string pattern_string) ;
vector<int> search_substring(string text_string, string pattern_string);
void get_partial_match_table(string pattern_string, int pattern_len, int pmt[]);

string file_name;
string data_string;


int main()
{	
	string input_string;
    data_string = getdata_string();
    cout<<"Enter file_name"<<endl;
    getline(cin, file_name); 
    count_words();
    count_lines();
   // vector<string> my_token = tokenize_sentence(input_string);
    //vector<string>::iterator it;
   /* for(it = my_token.begin();it!=my_token.end();++it )
    {
    	cout<< *it;
    }*/
}

void count_words()
{
	int count =0;
    char data[100];    
    ifstream file;    
    file.open(file_name.c_str());   
    while(!file.eof())
	{
		file>>data;
		cout<<data;
		count++;
	}
	cout<<"the no of words is: ";
	cout<<count;
	file.close();	
}

void count_lines()
{	
	int flag, count, lines;	
    char x;    
    ifstream file; 
	count = 0;
	flag = 0;
	lines = 0; 
    file.open(file_name.c_str());    
    while(!file.eof())
    {    	    	
    	x = file.get();
    	cout<<x;    	 
    	
		if(x=='\n')	flag = 1;
		
		if((x!='\n')&&(x!='\t')&&(x!=' '))
		{
			if(flag == 1) 
			{				
				lines++;
				flag = 0;
			}			
		}					
	}
	file.close();		
	cout<<"The no of lines is : ";
	if(lines==0) cout<<lines<<endl;
	else cout<<lines+1<<endl;
}

string getdata_string()
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

vector<string> tokenize_sentence(string sentence)
{
	vector<string> token_vector;			
	int size_sentence = sentence.size();	
	char tab2[size_sentence+1];	
	tab2[size_sentence+1] = '\0';
	strcpy(tab2, sentence.c_str());		
	int pre_index = 0;
	int post_index = 0;	
	vector<int> index_vector = KMP_implementation(sentence, " ");	
	index_vector.push_back(size_sentence-1);
	//cout<<"size of vector is "<<index_vector.size()<<endl;	
	string temp;
	string tokens[(index_vector.size())/2];	
	int p = 0;
	int m = 0;
	while(m<= index_vector.size()-2)
	{
		int temp_size = index_vector[m+1] - index_vector[m] + 1;			
		char arr[temp_size];
		int start = p;
		for(int k = 0;k<temp_size;k++)
		{									
			arr[k] = tab2[start];			
			start++;
		}		
		temp = arr;				
		m = m+2;	
		p = index_vector[m];	
	}	
	token_vector.push_back(temp);
	vector<string>::iterator it;
    for(it = token_vector.begin();it!= token_vector.end();++it )
    {
    	cout<< *it<<"   bhghsanjevhh";
    }
	return token_vector;
}

vector<int> KMP_implementation(string text_string, string pattern_string)   //This is implementation of KMP algorithm
{	vector<int> v;
	v = search_substring(text_string, pattern_string);
	return v;
}

vector<int> search_substring(string text_string, string pattern_string)
{
	vector<int> index_vector;
	index_vector.push_back(0);
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
			index_vector.push_back(i-j-1);
			index_vector.push_back(i-j+1);
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
	return index_vector;   //returns no of times a pattern is contained in it.
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
