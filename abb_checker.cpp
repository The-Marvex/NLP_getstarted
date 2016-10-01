#include<iostream>
#include<string>

using namespace std;
struct node
{
	node* parallel;
	node* child;
	char alphabet;
};


node* allocate_node();



int main()
{
	node* my_node = allocate_node();
}

node* allocate_node()
{	
	node* alpha = new node();
	cout<<"Enter the symbol"<<endl;
	cin>>alpha->alphabet;	
	alpha->child = NULL;
	alpha->parallel = NULL;
	return alpha;	
}

