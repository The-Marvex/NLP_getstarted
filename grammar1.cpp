#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

bool parse_for_syntax ();

int main()
{
	parse_for_syntax();
}

bool parse_for_syntax ()
{	
	vector <string> q_tokens(10);
	q_tokens.at(0) = "AT";
	q_tokens.at(1) = "AJ";
	q_tokens.at(2) = "PN";
	// q_tokens.at(3) = "VB";
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