#pragma once
#include"List.h"
#include"Map.h"
#include<string>
#include<iostream>
class Matrix {
public:
	Matrix(List<string>* data) {
		    map_City_name_to_index=new Map<string, int>();
		    map_index_to_name_City=new Map<int, string>();
			int N = data->get_size();
			int index_city = 0;
			int index_start_vertex = -1; //starting vertex
			for (int i = 0; i < N; i++) //we filled in all the indexes of different cities and count their number
			{
				string str_cur = data->at(i);
				int cur = str_cur.find(';'); //first occurrence ";"
				int cur1 = str_cur.find(';', cur + 1); //second occurrence ";"
				string str_name_city1 = str_cur.substr(0, cur); //getting the first city
				string str_name_city2 = str_cur.substr(cur + 1, cur1 - cur - 1); //getting the second city
				str_name_city2.erase(0, 1);
				if (!map_City_name_to_index->find_is(str_name_city1)) 
				{
					map_City_name_to_index->insert(str_name_city1, index_city);
					map_index_to_name_City->insert(index_city, str_name_city1);
					index_city++;
				}
				if (!map_City_name_to_index->find_is(str_name_city2)) 
				{
					map_City_name_to_index->insert(str_name_city2, index_city);
					map_index_to_name_City->insert(index_city, str_name_city2);
					index_city++;
				}
			}
			// filling in the path matrix
			size_of_matrix = index_city;
			matrix = new double* [size_of_matrix];
			for (int i = 0; i < size_of_matrix; i++)
				matrix[i] = new double[size_of_matrix];
			for (int i = 0; i < size_of_matrix; i++)
				for (int j = 0; j < size_of_matrix; j++)
					matrix[i][j] = INF;
			// filling in the price matrix
			for (int i = 0; i < N; i++) 
			{
				int price_1_to_2 = INF;
				int price_2_to_1 = INF;
				string str_cur = data->at(i);
				int cur = str_cur.find(';'); //first entering ;
				int cur1 = str_cur.find(';', cur + 1); //second entering ;
				int cur2 = str_cur.find(';', cur1 + 1); //third entering ;
				int cur3 = str_cur.find(';', cur2 + 1); //fourth entering ;
				string str_name_city1 = str_cur.substr(0, cur); //getting the first city
				string str_name_city2 = str_cur.substr(cur + 1, cur1 - cur - 1); //getting the second city
				str_name_city2.erase(0, 1);
				if (str_cur.substr(cur1 + 2, cur2 - 2 - cur1) != "N/A")
					price_1_to_2 = stof(str_cur.substr(cur1 + 2, cur2 - 2 - cur1));
				if (str_cur.substr(cur2 + 2, cur3 - 1) != "N/A")
					price_2_to_1 = stoi(str_cur.substr(cur2 + 2, cur3 - 2 - cur2));

				matrix[map_City_name_to_index->find(str_name_city1)][map_City_name_to_index->find(str_name_city2)] = price_1_to_2;

				matrix[map_City_name_to_index->find(str_name_city2)][map_City_name_to_index->find(str_name_city1)] = price_2_to_1;
			}
	}

	string Ford_Bellman(string start_City,string end_City) 
	{
		string cur;
		while (!map_City_name_to_index->find_is(start_City)) 
		{
			std::cout << "The departure city is missing, enter it again" << endl;
			std::cin >> start_City;
		}
		while (!map_City_name_to_index->find_is(end_City)) 
		{
			std::cout << "The arrival city is missing, enter it again" << endl;
			std::cin >> end_City;
		}
		int index_start_vertex = map_City_name_to_index->find(start_City); //find the index of the city of departure
		int index_end_vertex = map_City_name_to_index->find(end_City); //find the index of the city of departure
		double* distance = new double[size_of_matrix];
		int* pre = new int [size_of_matrix]; //ancestors
		for (int i = 0; i < size_of_matrix; i++) 
		{
			distance[i] = INF;
			pre[i] = -1;
		}		

		distance[map_City_name_to_index->find(start_City)] = 0;

		for (int i= 0; i< size_of_matrix-1; i++)
		{
			for (int j= 0; j< size_of_matrix; j++)
			{
				for (int k= 0; k< size_of_matrix; k++)
				{
					if (matrix[j][k] != INF)
					{
						if (distance[k] > distance[j] + matrix[j][k]) 
						{
							distance[k] = distance[j] + matrix[j][k];
							pre[k] = j;
						}
					}
				}
			}
		}
		if (distance[map_City_name_to_index->find(end_City)] != INF) 
		{
			cur = "The best route for the price: " + to_string(distance[map_City_name_to_index->find(end_City)]) + '\n';
			this->print_way(cur, start_City, end_City, distance, pre);
			cur.erase(cur.size() - 2);
			cur += '\n';
		}
		else {
			cur = "This route can't be built, try waiting for the flight schedule for tomorrow!";
		}
		return cur;
	}
	
private:
	void print_way(string& cur, string start_City, string end_City, double* distance,int* pre)
	{	
		List<int> way;
		for (int cur = map_City_name_to_index->find(end_City); cur != -1; cur = pre[cur])
			way.push_back(cur);
		way.reverse();

		cur=cur+"Way from "+start_City+" to "+end_City+": ";
		for (int i = 0; i < way.get_size(); ++i)
			cur=cur+map_index_to_name_City->find(way.at(i))+"->";
	}
	double** matrix;
	int size_of_matrix;
	Map<string, int>* map_City_name_to_index;
	Map<int, string>* map_index_to_name_City;
	const double INF = 1000000000;
};
