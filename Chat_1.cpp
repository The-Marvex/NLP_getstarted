#include<iostream>
#include<string>
#include<fstream>
using namespace std;

void read_file();
void test();
int main()
{
    read_file();
    //test();
}

void read_file()
{
    char data[100];
    string file_name;
    ifstream file;
    cout<<"Enter the name of the file you want to test"<<endl;
    cin>>file_name;
    file.open(file_name.c_str());
    file>>data;
    cout<<data;
    while(data != "xxx")
    {
        file>>data;
        cout<<data;
    }
}

void test()
{

   char data[100];
   /*cout << "Writing to the file" << endl;
   cout << "Enter your name: ";
   cin.getline(data, 100);
   outfile << data << endl;
   cout << "Enter your age: ";
   cin >> data;
   cin.ignore();
   outfile << data << endl;
   outfile.close();*/
   ifstream infile;
   infile.open("tagore.txt");
   cout << "Reading from the file" << endl;
   infile >> data;
   cout << data << endl;
   infile >> data;
   cout << data << endl;
   infile.close();
}

