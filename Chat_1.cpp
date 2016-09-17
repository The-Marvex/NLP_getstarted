#include<iostream>
#include<string.h>
#include<fstream>
#include<vector>

using namespace std;

void count_words();
void count_lines();
string getdata_string();
void tokenize_sentence(string sentence);

string file_name;
string data_string;


int main()
{	
    data_string = getdata_string();
    tokenize_sentence("sanjeev human pankaj neeraj");
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
	cout<<"The no of words is"<<endl;
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
	cout<<endl<<"The no of lines is: "<<endl;
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

void tokenize_sentence(string sentence)
{
	cout<<sentence<<endl;
	vector<string> token_vector;
	int size_sentence = sentence.size();
	int i= 0;
	char tab2[size_sentence+1];	
	tab2[size_sentence+1] = '\0';
	strcpy(tab2, sentence.c_str());		
	int pre_index = 0;
	int post_index = 0;
	int j = 0;		
	while(tab2[i]!='\0')
	{		
		if((tab2[i] == ' '))
		{

			post_index = i-1;			
			char temp_array[post_index - pre_index +1];
			cout<<"the size of token is: "<<(post_index - pre_index +1)<<endl;
			cout<<"pre_index is"<<pre_index<<endl;
			cout<<"post_index is"<<post_index<<endl;
			for(int k = pre_index;k<=post_index;k++)
			{
				temp_array[j] = tab2[k];
				cout<<temp_array[i]<<" ";
				j++;
			}
			string temp_token(temp_array);
			cout<<"the temptoken is given by: "<<temp_token<<endl;
			token_vector.push_back(temp_token);
			pre_index = (i+1);
		}	

		i++;		
	}

	cout<<"The tokens are: "<<endl;
	for(int i = 0;i<token_vector.size();i++)
	{
		cout<<token_vector[i]<<endl;		
	}
}

