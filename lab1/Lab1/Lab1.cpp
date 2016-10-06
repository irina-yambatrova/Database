#include "stdafx.h"
//#include "find.h"
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

bool Find(string &sample, string &text)
{
	const int p = 31;
	vector<long long> p_pow(max(sample.length(), text.length()));
	p_pow[0] = 1;
	for (size_t i = 1; i < p_pow.size(); ++i)
		p_pow[i] = p_pow[i - 1] * p;

	vector<long long> hashText(text.length());
	for (size_t i = 0; i < text.length(); ++i)
	{
		hashText[i] = (text[i] - 'a' + 1) * p_pow[i];
		if (i)  hashText[i] += hashText[i - 1];
	}

	long long hashSample = 0; 
	for (size_t i = 0; i < sample.length(); ++i)
	{
		hashSample += (sample[i] - 'a' + 1) * p_pow[i];
	}

	for (size_t i = 0; i + sample.length() - 1 < text.length(); ++i) 
	{
		long long cur_h = hashText[i + sample.length() - 1];
		if (i)  cur_h -= hashText[i - 1];

		if (cur_h == hashSample * p_pow[i]) 
			return true;
	}
}

void findUsername(string username, string str)
{ 
	if (Find(username, str) == 1)
	{
		cout << str.substr(0, str.find_first_of(",")) << ",";
	}
}

void inputUsernameAndOutputId(ifstream &inputFile)
{
	string username, str;
	cout << "Enter username: ";
	cin >> username;
	cout << "Record id: ";
	while (getline(inputFile, str))
	{
		findUsername(username, str);

	}
}

int main(int argc, char *argv[]) {

	if (argc != 2)
	{
		cout << "Error arguments!" << endl;
		return EXIT_FAILURE;
	}
	ifstream inputFile(argv[1]);
	if (!inputFile)
	{
		cout << "File not open!" << endl;
		return EXIT_FAILURE;
	}
	inputUsernameAndOutputId(inputFile);
	return EXIT_SUCCESS;
}

