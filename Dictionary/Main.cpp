#include <iostream>
#include <string>

#include "Dictionary.h"

using namespace std;

void GetPaths(string &in, string &out)
{
	cout << "Enter input and output file names : ";
	cin >> in >> out;
}

int main()
{
	string inputF, outputF;
#if _DEBUG
	inputF = "input.txt";
	outputF = "output.txt";
#else
	GetPaths(inputF, outputF);
#endif
	Dictionary_class* dict = new Dictionary_class(inputF, outputF);
	cout << "Added " << dict->Create() << " words" << endl;
	cin.get();
	return 0;
}