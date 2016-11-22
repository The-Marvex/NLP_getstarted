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

string strtrim(string sentence);
vector<string> tokenizer(string sentence);
vector<int> vector_generation(string query);
bool vector_Contains(string word, vector<string> in_search_vector);
void POS_tagging();
void get_partial_match_table(string pattern_string, int pattern_len, int pmt[]);
vector<int> get_white_spaces(string sentence);
bool dictionary_Contains(string word);
int get_index_in_vector(string word, vector<string> vector1);
void add_in_dictionary();
bool search_substring(string text_string, string pattern_string);
void suggest_command(string input);
int minimum_edit_distance(string alpha, string beeta);
int minimum_of(int a, int b, int c);
void remove_noise();
bool KMP_implementation(string text_string, string pattern_string);
vector<int> vector_generation(string query);
string get_data_string(string file_name);
int calculate_rank(string possible_soln, string query);
bool is_not_punctuation(char x);
bool parse_for_syntax ();
void parse_convo();
void get_convo_info(string file_name);
void print_vector(vector<string> vec);
vector <string> dictionary(50);
int dictionary_index;
vector <string> dictionary_desc(50);
void get_dictionary();
vector <string> conversation(4);
vector <vector<string> > keyword(4);

int main()
{	
	get_dictionary();			
	get_convo_info("text.txt");
	remove_noise();		
	parse_convo();		
	POS_tagging();

}

void extract_keywords(int i)
{

	vector <string> alpha;	
	int index  =0;
	int index2 = 0;
	for(int i = 0;i<conversation.size();i++)
	{
		alpha = tokenizer(conversation.at(i));
		for(int j = 0;j < alpha.size(); j++)
		{
			int k = get_index_in_vector(strtrim(alpha.at(j)), dictionary);

			if((dictionary_desc.at(k).compare("NN"))||(dictionary_desc.at(k).compare("VB"))||(dictionary_desc.at(k).compare("AJ")))
			{
				keyword.at(index).at(index2) = dictionary.at(k);
				index2++;
			}			
		}
		index++;
	}

}

void parse_convo()
{
	string line_of_convo;
	vector <string> tokens;
	int j;
	for(int i = 0;i<conversation.size();i++)
	{
		line_of_convo = conversation.at(i);
		tokens = tokenizer(line_of_convo);
		for(int j = 0;j<tokens.size();j++)
		{
			if(!dictionary_Contains(tokens.at(j)))
			{
				dictionary.at(dictionary_index) = strtrim(tokens.at(j));
				dictionary_desc.at(dictionary_index) = "NN";
				dictionary_index++;
			}			
		}
	}	
}

int get_index_in_vector(string word, vector<string> vector1)
{
	int index = 0;
	for(int  i = 0;i<vector1.size();i++)
	{
		if(vector1.at(i).compare(word) == 0)
			
			{
				index = i;
				break;
			}
	}
	return index;	
}

void POS_tagging()
{
	cout<<"The POS_tagging is given as: "<<endl;	
	vector<string> tokens;
	for(int i = 0;i<conversation.size();i++)
	{		
		tokens = tokenizer(conversation.at(i));				
		for(int j = 0;j<tokens.size();j++)
		{				
			int k = get_index_in_vector(strtrim(tokens.at(j)), dictionary);
			cout<<dictionary.at(k)<<" ";
			cout<<dictionary_desc.at(k)<<endl;
			//cout<<get_index_in_vector(strtrim(tokens.at(j)),dictionary_desc)<<endl;
		}
		cout<<endl<<endl;
	}
}



bool parse_for_syntax ()
{	
	vector <string> q_tokens(10);
	q_tokens.at(0) = "AT";
	q_tokens.at(1) = "AJ";
	q_tokens.at(2) = "PN";
	q_tokens.at(3) = "VB";
	q_tokens.at(3) = "PP";
	q_tokens.at(4) = "PN";

	int p = 0;
	bool article_start = false;
	bool has_adjective = false;
	bool has_preposition = false;
	bool accepted = false;
	while(p == 0)
	{
	
		if (q_tokens.at(0).compare("AT") == 0) article_start = true;

		if(article_start)
		{
			cout<<"has article_start"<<endl;
			if(q_tokens.at(1).compare("AJ") == 0) has_adjective = true;

			if(has_adjective)
			{
				cout<<"has adjective _start"<<endl;
				if((q_tokens.at(2).compare("NN") == 0)||(q_tokens.at(2).compare("PN") == 0))
				{
					cout<<"has some noun"<<endl;

					if(q_tokens.at(3).compare("VB") == 0)
					{
						cout<<"has verb "<<endl;

						if(q_tokens.at(4).compare("PP") == 0) has_preposition = true;

						if(has_preposition)
						{

							cout<<"has preposition"<<endl;
							if((q_tokens.at(5).compare("NN") == 0)||(q_tokens.at(5).compare("PN") == 0))
							{
								cout<<"has predicate noun"<<endl;
								accepted = true;
								cout<<"Accepted"<<endl;
								p =1;
							}
						}
						else
						{
							if((q_tokens.at(4).compare("NN") == 0)||(q_tokens.at(4).compare("PN") == 0))
							{
								cout<<"has no preposition"<<endl;
								cout<<"accepted"<<endl;
								accepted = true;
								p = 1;
							}
						}
					}

					else break;																
				}
				else
				{
					break;
				}
			}

			else
			{

				if((q_tokens.at(1).compare("NN") == 0)||(q_tokens.at(1).compare("PN") == 0))
				{
					if(q_tokens.at(2).compare("VB") == 0)
					{
						if(q_tokens.at(3).compare("PP") == 0) has_preposition = true;
						if(has_preposition)
						{
							if((q_tokens.at(4).compare("NN") == 0)||(q_tokens.at(4).compare("PN") == 0))
							{
								cout<<"accepted"<<endl;
								accepted = true;
								p = 1;
							}
						}
						else
						{
							if((q_tokens.at(3).compare("NN") == 0)||(q_tokens.at(3).compare("PN") == 0))
							{
								cout<<"accepted"<<endl;
								accepted = true;
								p = 1;
							}
						}
					}

					else break;																
				}

				else
				{
					break;
				}

			}
		}


		if(!article_start)
		{
			cout<<"has no article..YYY"<<endl;
			if(q_tokens.at(0).compare("AJ") == 0) has_adjective = true;

			if(has_adjective)
			{
				cout<<"has adjective..YYY"<<endl;
				if((q_tokens.at(1).compare("NN") == 0)||(q_tokens.at(1).compare("PN") == 0))
				{
					cout<<"HAS NOUN"<<endl;
					if(q_tokens.at(2).compare("VB") == 0)
					{
						cout<<"has verb"<<endl;
						if(q_tokens.at(3).compare("PP") == 0) has_preposition = true;
						if(has_preposition)
						{
							cout<<"has prepoSITION"<<endl;
							if((q_tokens.at(4).compare("NN") == 0)||(q_tokens.at(4).compare("PN") ==0))
							{
								cout<<"THIS IS predicate noun"<<endl;
								accepted = true;
								p = 1;
							}
						}
						else
						{
							cout<<"has NO preposition in sentence"<<endl;
							if((q_tokens.at(3).compare("NN") == 0)||(q_tokens.at(3).compare("PN") == 0))
							{
								accepted = true;
								p = 1;
							}
						}
					}

					else break;																
				}
				else
				{
					break;
				}
			}
			else
			{
				cout<<"has NO adjective..YYY"<<endl;

				if((q_tokens.at(0).compare("NN") == 0)||(q_tokens.at(0).compare("PN") == 0))
				{
					cout<<"FIRST WORD AS noun"<<endl;
					if(q_tokens.at(1).compare("VB") == 0)
					{

						cout<<"second WORD AS verb"<<endl;
						if(q_tokens.at(2).compare("PP") == 0) has_preposition = true;
						if(has_preposition)
						{
							cout<<"has a preposition"<<endl;
							if((q_tokens.at(3).compare("NN") == 0)||(q_tokens.at(3).compare("PN") == 0))
							{
								cout<<"Final noun"<<endl;
								accepted = true;
								p = 1;
							}
						}
						else
						{
							cout<<"no preposition YYYY"<<endl;
							if((q_tokens.at(2).compare("NN") == 0)||(q_tokens.at(2).compare("PN") == 0))
							{
								cout<<"Final noun"<<endl;
								cout<<"Accepted"<<endl;
								accepted = true;
								p = 1;
							}
						}
					}

					else break;																
				}
				
				else
				{
					break;
				}

			}

		}
				
	}

	cout<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<endl;
	if(accepted) cout<<"VALID INPUT"<<endl;
	else cout<<"INVALID INPUT, plaese ask acc to grammar"<<endl;
	return accepted;
}

void remove_noise()
{
	vector <int> noise_index(10);
	vector <string> convo_tokens(10);
	int index;
	string corrected_convo = "";
	corrected_convo.clear();
	for(int i = 0; i<conversation.size();i++)
	{		
		convo_tokens = tokenizer(conversation.at(i));		
		cout<<endl;
		index = 0;
		for(int j = 0;j<convo_tokens.size();j++)
		{			

			string temp = strtrim(convo_tokens.at(j));
						
			if(!dictionary_Contains(temp))
			{											

				if(temp.size() <= 3)					
				{							

					if((temp.compare("ugh") == 0 )||(temp.compare("hmm") == 0)||(temp.compare("ohh") == 0)
						||(temp.compare("ahh") == 0)) 
					{							
						noise_index.at(index) = j;
						index ++;
					}	

					else					
					{
						corrected_convo = corrected_convo + " " + temp;
					}				
				}

				else
				{
					if((KMP_implementation(convo_tokens.at(j),"mmm"))||(KMP_implementation(convo_tokens.at(j),"hhh"))
						||(KMP_implementation(convo_tokens.at(j),"ooo"))
						||(KMP_implementation(convo_tokens.at(j),"ppp"))||(KMP_implementation(convo_tokens.at(j),"eee"))
						||(KMP_implementation(convo_tokens.at(j),"haha"))||(KMP_implementation(convo_tokens.at(j),"hehe")))
					{											
						noise_index.at(index) = j;
						index ++;
					}
					else
					{
						corrected_convo = corrected_convo + " " + temp;
					}
				}
			}

			else
			{
				corrected_convo = corrected_convo + " " + temp;
			}
		}
				
		conversation.at(i) = corrected_convo;	
		corrected_convo.clear();	
	}		
}



bool search_substring(string text_string, string pattern_string)
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
			//cout<<pattern_string<<" occurred at: "<<i-j<<endl;
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
	if(count >0) return true;
	else return false;
}

bool KMP_implementation(string text_string, string pattern_string) //This is implementation of KMP algorithm
{ 
	bool x = search_substring(text_string, pattern_string);
	return x;
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



int minimum_edit_distance(string alpha, string beeta)
{
	alpha = '#' + alpha;
	beeta = "#" + beeta;
	int alpha_size = alpha.size();
	int beeta_size = beeta.size();
	char alpha_array[alpha_size+1];
	char beeta_array[beeta_size+1];
	strcpy(alpha_array, alpha.c_str());
	strcpy(beeta_array, beeta.c_str());
	int distance_table[alpha_size+1][beeta_size+1];
	for(int i = 0;i<=alpha_size;i++)
	{
		distance_table[i][0] = i;
	}
	for(int i = 0;i<=beeta_size;i++)
	{
		distance_table[0][i] = i;
	}
	for(int i = 1;i<alpha_size;i++)
	{
		for(int j = 1;j<beeta_size;j++)
		{
			if(alpha_array[i] == beeta_array[j])
			{
				distance_table[i][j] = minimum_of((distance_table[i-1][j]+1),(distance_table[i][j-1]+1),(distance_table[i-1][j-1]));
			}
			else
			{
				distance_table[i][j] = minimum_of((distance_table[i-1][j]+1),(distance_table[i][j-1]+1),(distance_table[i-1][j-1]+2));
			}
		}
	}
	return distance_table[alpha.size()-1][beeta.size()-1];
}

int minimum_of(int a, int b, int c)
{
	int temp = 100;
	if(a<b) temp = a;
	if(temp<c) return temp;
	else return c;
}


void suggest_command(string input)

{	
	int index, min, temp;
	index = 0; min= 1000;
	bool x;
	x = false;
	for(int i = 0;i<9;i++)
	{
		//temp = minimum_edit_distance(input, arr[i]);		
		if(min>temp) 
		{
			min = temp;
			index = i;
		}			
	}		
	if ((min <= 3)&&(min>=1)) 
	{
		//cout<<"Do you mean '"<<arr[index]<<"'"<<endl;
		x = true;
	}		
	cout<<endl;
}



void get_convo_info(string file_name)
{	
	ifstream file(file_name.c_str());
    string word;
    int index = 0;
    char x ;
    word.clear();       
    while ((x = file.get())!= EOF)
    {    	
    	if(x == '\n')
        {        	
        	conversation.at(index) = word;
        	index++;
        	word.clear();
        }     
    	else if(!is_not_punctuation(x)) word = word + " ";    	
    	else word  = word + x;
    }

    conversation.at(index) = word;
    file.close();    

    print_vector(conversation);
    cout<<endl;
}


string get_data_string(string file_name)
{
	ifstream file(file_name.c_str());
    string word;
    char x ;
    word.clear();
    int count  = 0;
    while (((x = file.get())!= EOF))
    {
    	if(is_not_punctuation(x))
        word = word + x;
    	else
    	word = word + " ";
    }
    file.close();
    return word;   
}

bool is_not_punctuation(char x)
{
	if((x==',')||(x=='.')||(x==':')||(x=='!')||(x=='?')||(x==':')||(x==';'))
	{
		return false;
	}
	else return true;
}

void get_dictionary()
{
	dictionary_index = 0;
	XMLDocument xmlDoc1;
	XMLError eResult = xmlDoc1.LoadFile("dictionary.xml");
	XMLNode *pRoot = xmlDoc1.FirstChild();
	string my_word;
	for(XMLElement* e=pRoot->FirstChildElement("entry");e!=NULL;e=e->NextSiblingElement("entry"))
	{
		XMLElement* token = e->FirstChildElement("token");
		const char* word = token->GetText();		
		int size = strlen(word);		
		my_word.assign(word, size);
		dictionary.at(dictionary_index) = word;		
		
		string tag = e->Attribute("tags");	
		dictionary_desc.at(dictionary_index) = tag;		
		dictionary_index ++;	
	}

}

vector<int> vector_generation(string query)
{	
	int index = 0;
	vector <string> tokens = tokenizer(query);
	vector <int> query_vector(dictionary.size());	
	for(int i = 0;i< dictionary.size();i++)
	{
		if(vector_Contains(dictionary.at(i), tokens))
		{									
			query_vector.at(index) = 1;
		}

		else
		{						
			query_vector.at(index) = 0;
		}		
		index++;
	}		
	return query_vector;	
}

void print_vector(vector<string> vec)
{
	for(int i = 0;i<vec.size();i++)
	{
		cout<<vec.at(i)<<endl;
	}
	cout<<endl;
}


bool vector_Contains(string word, vector<string> in_search_vector)
{
	int p = 0;	
	for(int i = 0;i< in_search_vector.size();i++)
	{
		if(word.compare(in_search_vector.at(i)) == 0)
		{
			p = 1;
			break;			
		}
	}

	if(p==0) return false;
	else return true;

}



int calculate_rank(string possible_soln, string query)
{
	cout<<"ENTERED"<<endl;
	int sum = 0;
	vector<int> candidate_v = vector_generation(possible_soln);
	vector<int> query_v = vector_generation(query);

	cout<<candidate_v.size()<<"  "<<query_v.size()<<endl;

	for(int i = 0;i<candidate_v.size();i++)
	{
		sum = sum + candidate_v.at(i)*query_v.at(i);
	}
	return sum;
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




vector<string> tokenizer(string sentence)
{	
	string sentence1 = strtrim(sentence);
	int size;	
	vector<int> index_vector = get_white_spaces(sentence1);	
	for(int i = 0;i<index_vector.size();i++)
	{
		if((i!=0)&&(index_vector.at(i) == 0))
		{
			size = i;
			break;
		}
	}	
	vector<string> tokens (size/2);
	int pre,post,length,i;
	i= 0;
	length = 0;
	string temp;
	int one;
	while(i < index_vector.size())
	{
		if((i ==0)||(index_vector.at(i) !=0))
		{
			temp.clear();
			pre = index_vector.at(i);
			post = index_vector.at(i+1);
			for(int j = pre;j<=post+1;j++)
			{
				temp = temp + sentence[j];			
				one  = j;
			}			
			tokens.at(length) = temp;
			length++;
		}
		i = i+2;
	}	
	//print_vector(tokens);
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
