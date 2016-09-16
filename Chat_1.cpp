#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void count_words();
void count_lines();
string getdata_string();

string file_name;
string data_string;


int main()
{
	cout<<"Enter the name of the file you want to test"<<endl;
    cin>>file_name;
   // count_words();    
   //count_lines();
    data_string = getdata_string();
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

