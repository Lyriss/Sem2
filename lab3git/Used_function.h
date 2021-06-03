#pragma once
#include<iostream>
#include<fstream>
void InputDataFromFile(List<string>* data, ifstream& file) //entering from a file
{
	while (!file.eof()) {
		string s1;
		getline(file, s1);
		data->push_back(s1);
	}
}