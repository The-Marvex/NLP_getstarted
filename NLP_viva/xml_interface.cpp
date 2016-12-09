
// Throughout the coe, we have used .c_str() to convert string to C-style pointer to an array of
// null terminated characters

#include <iostream>
// #include <regex>
#include <string>

// Include the following for xml file handling
#include "tinyxml2.h"
#include "tinyxml2.cpp"

using namespace std;
using namespace tinyxml2;

// As I use for statements a lot, so I have defined it for a shorter way.
#define fr(i,n) for(i=0;i<n;i++)

// Just copy and paste
#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif


// xmlDoc is used for loading and saving to xml file
XMLDocument xmlDoc;
// root tag
XMLNode * pRoot;

void createXMLDocument(){
	pRoot = xmlDoc.NewElement("Root");
	xmlDoc.InsertFirstChild(pRoot);
}

void addDataToXMLDocument(string elementName, string text, string attrib_key[][2], int size){
	XMLElement * pElement = xmlDoc.NewElement(elementName.c_str());
	int i;
	// (sizeof attrib_key/ sizeof attrib_key[0]) => This wont work as all we have is a pointer.
	// It will return 0 
	// We need to know the size. Hence we pass the size as an argument
	fr(i, size){
		// Iterate through the array and add the attributes and actual text.
		pElement->SetAttribute(attrib_key[i][0].c_str(), attrib_key[i][1].c_str());
	}
	pElement->SetText(text.c_str());
	pRoot->InsertEndChild(pElement);
}

void addDatatoXMLElement(XMLElement * pElement, string elementName, string text, string attrib_key[][2], int size){
	XMLElement * pElement1 = xmlDoc.NewElement(elementName.c_str());
	int i;
	// (sizeof attrib_key/ sizeof attrib_key[0]) => This wont work as all we have is a pointer.
	// It will return 0 
	// We need to know the size. Hence we pass the size as an argument
	fr(i, size){
		// Iterate through the array and add the attributes and actual text.
		pElement1->SetAttribute(attrib_key[i][0].c_str(), attrib_key[i][1].c_str());
	}
	pElement1->SetText(text.c_str());
	pElement->InsertEndChild(pElement1);
}

XMLElement* createChild(string elementName, string attrib_key[][2], int size){
	XMLElement * pElement = xmlDoc.NewElement(elementName.c_str());
	int i;
	fr(i, size){
		// Iterate through the array and add the attributes and actual text.
		pElement->SetAttribute(attrib_key[i][0].c_str(), attrib_key[i][1].c_str());
	}
	pRoot->InsertEndChild(pElement);
	return pElement;
}

int saveXMLDocument(string name){
	XMLError eResult = xmlDoc.SaveFile(name.c_str());
	XMLCheckResult(eResult);
}

int readXMLDocument(string name){
	XMLError eResult = xmlDoc.LoadFile(name.c_str());
	XMLCheckResult(eResult);
}

int readDataFromXML(){
	// We first need the root child
	XMLNode * pRoot = xmlDoc.FirstChild();
	if (pRoot == NULL) cout << XML_ERROR_FILE_READ_ERROR << endl;

	// --------------------x-------------------
	// XMLElement * pElement = pRoot->FirstChildElement("IntValue");
	// if (pElement == NULL) cout << XML_ERROR_PARSING_ELEMENT << endl;
	// int iOutInt;
	// XMLError eResult = pElement->QueryIntText(&iOutInt);
	// XMLCheckResult(eResult);
	// cout << iOutInt << endl;

	// pElement = pRoot->FirstChildElement("Date");
	// if (pElement == NULL) cout << XML_ERROR_PARSING_ELEMENT << endl;

	// int iOutDay, iOutYear;

	// eResult = pElement->QueryIntAttribute("day", &iOutDay);
	// XMLCheckResult(eResult);
	// cout << iOutDay << endl;

	// eResult = pElement->QueryIntAttribute("year", &iOutYear);
	// XMLCheckResult(eResult);

	// cout << iOutYear << endl;
	// ------------------x-----------------------

	// Parsing the list of words.
	XMLElement * pListElement = pRoot->FirstChildElement("word");
	while (pListElement != NULL){
		string iOutListValue;
		iOutListValue = pListElement->GetText();
		cout << iOutListValue << endl;

		// move to next word tag
		pListElement = pListElement->NextSiblingElement("word");
	}
}

// int main(){
	// string s = "Hello, my name is Pankaj. I am a good boy.";
	// final String regex = "(?:\\s?)((?:(?:[\\\"\\'].*?(?:[\\.?!][\\\"\\'](?:\\s[a-z].*?[\\.?!])?|[\\\"\\'].*?[\\.?!]))|(?:[^.?!\\\"]{2,1000}[\\.?!]?)))";
void extra(){
	createXMLDocument();
	string attributes[][2]={{"a", "b"}, {"d", "e"}};
	int size = sizeof attributes/ sizeof attributes[0];
	addDataToXMLDocument("word", "string text 1", attributes, size);
	addDataToXMLDocument("word", "string text 2", attributes, size);
	saveXMLDocument("SavedData.xml");
	readXMLDocument("SavedData.xml");
	readDataFromXML();
}
