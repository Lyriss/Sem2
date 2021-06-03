#include<iostream> 
#include"Map.h"
#include <fstream>
#include<string>
#include"adjacency_matrix.h"
#include"Used_function.h"
using namespace std;
int main() {
	ifstream input("input.txt");
	List<string>* list_fly = new List<string>();
	string city_Start;
	string city_End;
	InputDataFromFile(list_fly, input);
	cout << "Flight schedule: " << endl;
	for (int i = 0; i < list_fly->get_size(); i++)
		cout << list_fly->at(i) << endl;
	cout << "Enter the departure city" << endl;
	getline(cin, city_Start);
	cout << "Enter your arrival city" << endl;
	getline(cin, city_End);
	Matrix* matrix_ford_bellman = new Matrix(list_fly);
	cout<<matrix_ford_bellman->Ford_Bellman(city_Start,city_End);
}


