#include<fstream>

#include"Network.h"
#include<iostream>
using namespace std;
int main()
{
	try {
		int source, sink;
		ifstream input("Input4.txt");
		Network* transnet = new Network(input);
		int MaxFlow = transnet->max_flow();
		cout << endl << "Max Flow is " << MaxFlow << endl;
		delete transnet;
	}

	catch (exception & ex) {
		std::cout << ex.what();
	}

	getchar();
}