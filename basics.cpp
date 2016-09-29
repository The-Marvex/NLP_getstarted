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

string file_name;
string data_string;


int main()
{		
	/*string input_string;
    cout<<"Enter something"<<endl;
    getline(cin, input_string);    
    vector<string> my_token = tokenize_sentence(input_string);
    for(int x = 0;x<my_token.size();x++)	
	{
		cout<<my_token.at(x)<<" ";
	}*/
		cout<<"Enter the file name"<<endl;
		getline(cin, file_name);
		data_string = get_data_string();
		text2sentence(data_string);
}

vector <string> text2sentence(string text)
{
	int init_vec_size = 10;
	int k;
	int b = 0;
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
    	if(text_array[i] == '.')
    	{    		
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

vector<string> tokenize_sentence(string sentence)
{
	int init_size_vector = 20;
	vector<string> token_vector(init_size_vector);			
	int size_sentence = sentence.size();	
	char tab2[size_sentence+1];	
	tab2[size_sentence+1] = '\0';
	strcpy(tab2, sentence.c_str());	
	int index = 0;	
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
		token_vector.at(index) = temp;
		index++;	
		if(index == init_size_vector) 
		{
			token_vector.resize(2*init_size_vector);
			init_size_vector = 2*init_size_vector;
		}
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
