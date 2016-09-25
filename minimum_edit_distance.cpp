#include<iostream>
#include<string.h>
using namespace std;

int minimum_edit_distance(string alpha, string beeta);

int main()
{	
	string alpha, beeta;
	cout<<"enter the strings"<<endl;
	cin>>alpha;
	cout<<endl;
	cin>>beeta;
	cout<<endl;
	int distance = minimum_edit_distance(alpha, beeta);
	cout<<"The minimum edit distance is given by: "<<distance;
	
}
int minimum_edit_distance(string alpha, string beeta)
{
	int alpha_size = alpha.size();
	int beeta_size = beeta.size();
	char alpha_array[alpha_size+1];
	char beeta_array[beeta_size+1];
	alpha_array[alpha_size] = '\0';
	beeta_array[beeta_size] = '\0';
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
		for(int j = 0;j<beeta_size;j++)
		{
			if(alpha_array[i] == beeta_array[j])
			{
				distance_table[i][j] = min((distance_table[i-1][j]+1),(distance_table[i][j-1]+1),(distance_table[i-1][j-1]));
			}
			else
			{
				distance_table[i][j] = min((distance_table[i-1][j]+1),(distance_table[i][j-1]+1),(distance_table[i-1][j-1]+2));	
			}
		}
	}

	for(int i = 1;i<alpha_size;i++)
	{
		for(int j = 0;j<beeta_size;j++)
		{
			cout<<distance_table[i][j]<<" ";
		}
		cout<<endl;
	}

	return 5;
	
}
