#pragma once
#include<fstream>
#include"Map.h"
#include"Queue.h"
#include<string>
#include"Algorithm.h"
class Network {
public:
	~Network() {
		for (int i = 0; i < VertexCount; ++i) {
			Graph[i].clear();
			delete[]Capacity[i];
			delete[]FlowPassed[i];
		}
		delete[]ParList;
		delete[]CurrentPathC;
	}

	Network(ifstream& file) {
		Map<char, int>* Map_from_char_to_number = new Map<char, int>();
		Validators(file, Map_from_char_to_number);
		file.clear();
		file.seekg(ios::beg);

		while (!file.eof()) {
			string s1;
			int vert1, vert2, cap;
			getline(file, s1);
			vert1 = Map_from_char_to_number->find(s1[0]);
			vert2 = Map_from_char_to_number->find(s1[2]);
			Capacity[vert1][vert2] = stoi(s1.substr(4));
			Graph[vert1].push_back(vert2);
			Graph[vert2].push_back(vert1);
		}
	}

	void Validators(ifstream& file, Map<char, int>*& Map_from_char_to_number) {
		int vert1, vert2, cap;
		VertexCount = 0;
		Map_from_char_to_number = new Map<char, int>();
		int str_num = 1;
		while (!file.eof()) {
			string s1;
			getline(file, s1);
			if (s1.size() >= 5) { //greater than or equal to 5, because this is the minimum possible input(two letters, two spaces,one digit)
				if (!((s1[0] >= 'A' && s1[0] <= 'Z') && (s1[1] == ' '))) {
					throw std::exception(string(("Error entering the first character in the string or missing a space after it. Check the correctness of the input in the file and correct these errors in the line under the number: " + to_string(str_num))).c_str());
				}
				if (!((s1[2] >= 'A' && s1[2] <= 'Z') && (s1[3] == ' '))) {
					throw std::exception(string(("Error entering the second character in the string or missing a space after it. Check the correctness of the input in the file and correct these errors in the line under the number: " + to_string(str_num))).c_str());
				}
				string cur;

				for (int i = 4; i < s1.size(); ++i) {
					if (s1[i] >= '0' && s1[i] <= '9')
						cur += s1[i];
					else {
						throw std::exception(string(("Error entering the third character (bandwidth) in the string or the presence of a space after it.Please note that the bandwidth cannot be negative. Check that you entered the file correctly and correct these errors in the line number: " + to_string(str_num))).c_str());
					}
				}
				if (!Map_from_char_to_number->find_is(s1[0])) {
					Map_from_char_to_number->insert(s1[0], VertexCount);
					++VertexCount;
				}
				if (!Map_from_char_to_number->find_is(s1[2])) {
					Map_from_char_to_number->insert(s1[2], VertexCount);
					++VertexCount;
				}

			}
			else
			{
				throw std::exception(string(("A data-entry error. Check the correctness of the input in the file and correct these errors in the line under the number: " + to_string(str_num))).c_str());
			}
			++str_num;
		}
		if (Map_from_char_to_number->find_is('S'))
			SourceVertex = Map_from_char_to_number->find('S');
		else {
			throw std::exception("Source is missing");
		}

		if (Map_from_char_to_number->find_is('T'))
			SinkVertex = Map_from_char_to_number->find('T');
		else {
			throw std::exception("Sink is missing");
		}
		Graph = new List<int>[VertexCount];
		FlowPassed = new int* [VertexCount];
		Capacity = new int* [VertexCount];
		ParList = new int[VertexCount];
		CurrentPathC = new int[VertexCount];
		for (int i = 0; i < VertexCount; ++i) {
			FlowPassed[i] = new int[VertexCount];
			Capacity[i] = new int[VertexCount];
			for (int j = 0; j < VertexCount; ++j) {
				FlowPassed[i][j] = 0;
				Capacity[i][j] = 0;
			}
		}
	}
	
	int BFS(int Source, int Sink) //breadth first search 
	{
		for (int i = 0; i < VertexCount; ++i) {
			ParList[i] = -1;
			CurrentPathC[i] = 0;
		}
		Queue<int> q; //declare queue vector 
		q.enqueue(Source);
		ParList[Source] = -1; 
		CurrentPathC[Source] = 999; 
		while (!q.empty()) //if q is not empty
		{
			int CurrNode = q.dequeue();
			for (int i = 0; i < Graph[CurrNode].get_size(); i++)
			{
				int to = Graph[CurrNode].at(i);
				if (ParList[to] == -1)
				{
					if (Capacity[CurrNode][to] - FlowPassed[CurrNode][to] > 0)
					{
						ParList[to] = CurrNode;
						CurrentPathC[to] = minT(CurrentPathC[CurrNode], Capacity[CurrNode][to] - FlowPassed[CurrNode][to]);
						if (to == Sink)
						{
							return CurrentPathC[Sink];
						}
						q.enqueue(to);
					}
				}
			}
		}
		return 0;
	}

	int max_flow() {
		int max = EdmondsKarp(SourceVertex, SinkVertex);
		return max;
	}

	int EdmondsKarp(int Source, int Sink)
	{
		int MaxFlow = 0;
		while (true)
		{
			int Flow = BFS(Source, Sink);
			if (Flow == 0)
			{
				break;
			}
			MaxFlow += Flow;
			int CurrNode = Sink;
			while (CurrNode != Source)
			{
				int PrevNode = ParList[CurrNode];
				FlowPassed[PrevNode][CurrNode] += Flow;
				FlowPassed[CurrNode][PrevNode] -= Flow;
				CurrNode = PrevNode;
			}
		}
		return MaxFlow;
	}

private:
	int SourceVertex;
	int SinkVertex;
	List<int>* Graph;
	int** Capacity;
	int** FlowPassed;
	int* ParList;
	int* CurrentPathC;
	int VertexCount;
};