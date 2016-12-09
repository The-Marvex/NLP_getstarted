#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>

using namespace std;

void count_words();
void count_lines();
string get_data_string();
vector<string> tokenize_sentence(string sentence);
vector<int> KMP_implementation(string text_string, string pattern_string) ;
vector<int> search_substring(string text_string, string pattern_string);
void get_partial_match_table(string pattern_string, int pattern_len, int pmt[]);
vector <string> text2sentence(string text);
string strtrim(string sentence);
vector<int> get_white_spaces(string sentence);

string file_name;
string data_string;


int main()
{			
		file_name = "nlp.txt";
		string text = get_data_string();
		cout<<text<<endl;
		vector <string> lines = text2sentence (text);
		count_lines();

}

vector <string> text2sentence(string text)
{
	int init_vec_size = 10;
	int k;
	int b = 0;
	int no_of_lines =0;
	int pre_index =0;
	int post_index = 0;
    int text_size = text.size();    
    char text_array[text_size+1];
    text_array[text_size] = '\0';
    for(int i = 0;i<=text_size;i++)
    {
    	cout<<text_array[i];
    }
    strcpy(text_array, text.c_str());
    vector<string> sentences(init_vec_size);
    vector<char> temp_vector(50);
    string str;	
    int i = 0;    

    while(text_array[i]!='\0')
    {
    	if((text_array[i] == '.')&&(text_array[i+1]!='.'))
    	{    		
    		no_of_lines++;
    		post_index = i;
    		temp_vector.resize(post_index - pre_index +1);
    		k = 0;
    		for(int y = pre_index;y<post_index;y++)
    		{    			
    			temp_vector.at(k) = text_array[y];
    			k++;
    		}
    		pre_index = post_index+2;
    		k = 0;    
			while(k<temp_vector.size())    				
			{				
				str = str + temp_vector.at(k);
				k++;
			}			
    	}

    	sentences.at(b) = str;
    	str.clear();
    	b++;    		
		if(b == init_vec_size) 
		{
			sentences.resize(2*init_vec_size);
			init_vec_size = (2*init_vec_size);
		}
    	i++;    	
    }

    for(int i = 0;i<sentences.size();i++)
    {
    	cout<<sentences.at(i)<<endl;
    }
    
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
		count++;
	}
	cout<<"The number of words is: ";
	cout<<count<<endl;
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
	cout<<"The number of lines is: ";
	if(lines==0) cout<<lines<<endl;
	else cout<<(lines+1)<<endl;
}

string get_data_string()
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

vector<string> tokenizer(string sentence)
{
	int p;
	sentence = strtrim(sentence);	
	vector<string> tokens (10);		
	vector<int> index_vector = get_white_spaces(sentence);	
	int pre,post,length,i;
	i= 0;
	length = 0;
	string temp;
	while(i < index_vector.size())
	{
		if((i ==0)||(index_vector.at(i) !=0))
		{
			temp.clear();
			pre = index_vector.at(i);
			post = index_vector.at(i+1);			
			for(int j = pre;j<=post;j++)
			{
				temp = temp + sentence[j];
			}			
			tokens.at(length) = temp;
			length++;		
		}

		i = i+2;
	}	
	return tokens;
}

vector<int> get_white_spaces(string sentence)
{	
	vector<int> space_index(20);
	char x;
	int i = 0;
	int j,k;
	k = 0;
	int diff = 0;	
	space_index.at(k) = 0;
	k++;
	while(i<sentence.size())
	{		
		if(sentence[i] == ' ')
		{
			space_index.at(k) = i-1;
			k++;
			j = i;
			while(j<sentence.size()-1)
			{				
				if((sentence[j]==' ')&&(sentence[j+1]!=' ')) 
				{			
					space_index.at(k) = j+1;
					k++;
					break;
				}
				else j++;
			}						
			diff = j-i;
			i = j+1;			
		}	
		else i++;			
		 
	}
	space_index.at(k) = sentence.size()-1;	
	return space_index;
}

string strtrim(string sentence)
{	
	int i = 0;
	sentence = sentence.c_str();
	int j = sentence.size()-1;	
	char x;		
	while(i < j)
	{
		if(sentence[0] != ' ') 
		{
				i = 0;
				break;
		}
		else if((sentence[i] == ' ') && (sentence[i+1] != ' ')) 
		{
				i = i+1;
				break;
		}
		else
		{
			i++;			
		}
	}	
	while(j>0)
	{
		if(sentence[sentence.size()-1] != ' ') break;		
		else if((sentence[j] == ' ') && (sentence[j-1]!=' ')) 
		{	
			j = j-1;
			break;
		}
		else j--;
	}
	string trm_str;
	trm_str.clear();	

	for(int k = i; k<=j; k++)
	{
		x = sentence[k];
		trm_str = trm_str + x;		
	}	
	return trm_str;

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
