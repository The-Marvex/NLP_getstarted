#include <iostream>
#include "tinyxml2.cpp"
#include "tinyxml2.h"

using namespace std;
using namespace tinyxml2;
void create_dictionary();

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { cout<<"error"; return a_eResult; }
#endif
int main()
{
	create_dictionary();
}

void create_dictionary()
{
	
	XMLDocument xmlDoc1;
	XMLError eResult = xmlDoc1.LoadFile("dictionary.xml");
	XMLNode *pRoot = xmlDoc1.FirstChild();

	for(XMLElement* e=pRoot->FirstChildElement("entry");e!=NULL;e=e->NextSiblingElement("entry"))
	{
		XMLElement* token = e->FirstChildElement("token");
		const char* word = token->GetText();
		cout<<word<<endl;
		string tag=e->Attribute("tags");
		cout<<tag<<endl;
	}

}