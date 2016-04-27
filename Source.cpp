#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <string>

using namespace std;

int extraction_method(int val)
{
	//char *intStr;
	//itoa(val, intStr, 10);
	string str = to_string(val);
	string hash;

	hash.append(1,str[2]);
	hash.append(1,str[4]);
	hash.append(1,str[6]);
	hash.append(1,str[7]);
	

	
	int hash_address;

	
	hash_address = stoi(hash);


	return hash_address;
}

bool quadratic(int value, int *& hash_table, int i, int M)
{
	unsigned int pos;
	

	pos = (extraction_method(value) + i*i) % M;

	if (hash_table[pos] == 0)
	{
		hash_table[pos] = value;
		return true;
	}
	else
	{
		while (hash_table[pos] != 0)
		{
			i++;
			pos = (extraction_method(value) + i*i) % M;
		}
		hash_table[pos] = value;
		return true;
	}
	
}



int main()
{
	string file;

	cout << "Please enter the file name to read: "; 
	getline(cin, file);  //sets user input as file string


	ifstream infile;
	ofstream testfile;
	ofstream myfile;

	
	testfile.open("my_results.txt");
	//testfile << "test"; - test if writes to file correctly
	vector<int> num;
	char cNum[10];
	infile.open(file);   //opens file that user names 
	
	//while loop makes sure file is open before program continues
	while (!infile.is_open())
	{
		cout << "Incorrect file. Please enter a new file name: ";
		getline(cin, file);
		infile.open(file);
	}
	
	
	int i = 0;
	if (infile.is_open()) //double checks file is open
	{
		//testfile << "Input: ";
		while (infile.good())
		{
			infile.getline(cNum, 10, ',');  //gets strings separated by commas 
			num.push_back(atoi(cNum)); //converts the strings into integers
			if (infile.peek() == EOF)
				testfile << atoi(cNum);
			else
				testfile << atoi(cNum) << ",";
		}
		infile.clear();
		infile.close();
	}

	int file_size = num.size(); //get size of file
	//cout << file_size;

	int *hash_table = new int[file_size];

	
	for (int i = 0; i<file_size; i++)    //initialize the hash table to contain 0s
		hash_table[i] = 0;

	//cout << extraction_method(num[0]) << endl;

	int index, max;
	string str;

	cout << "Input a number between 1 and 450 million: "; 

	getline(cin, str);
	index = stoi(str);

	if (index < 1 || index > 450000000)
	{
		cout << "Not in range. \nInput a number between 1 and 450 million: ";
		getline(cin, str);
		index = stoi(str);
	}
	// cout << max << endl;


	for (int i = 0; i<file_size; i++)    //hash the elements in array_of_numbers into the hash_table
	{
		index = extraction_method(num[i]);
		if (hash_table[index] == 0)
			hash_table[index] = num[i];
		else
		{
			cout << "COLLISION! Fear not... I'll resolve it!\n";
			quadratic(num[i], hash_table, index, file_size);
		}
	}

	myfile.open("hashed_socials.txt");

	for (int i = 0; i < file_size; i++)
	{
		if (i = file_size - 1)
		{
			myfile << hash_table[i];
		}
		else
		{
			myfile << hash_table[i] << ", ";
		}
	}

	system("pause");
}