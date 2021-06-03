#include "pch.h"
#include "CppUnitTest.h"
#include"../FordBellman/adjacency_matrix.h"
#include"../FordBellman/List.h"
#include"../FordBellman/Map.h"
#include"../FordBellman/Used_function.h"
#include<fstream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestFordBellman
{
	TEST_CLASS(UnitTestFordBellman)
	{
	public:
		
		TEST_METHOD(TestExampleWayIsAvaible)
		{
			ifstream input("d:\\Учеба\\АиСд\\FordBellman\\UnitTestFordBellman\\input1.txt");
			List<string>* list_fly = new List<string>();
			string city_Start = "Velikiy Novgorod";
			string city_End = "Moscow";
			InputDataFromFile(list_fly, input);
			Matrix* matrix_floid_uorshell = new Matrix(list_fly);
			string cur = "The best route for the price: 20.000000\nWay from Velikiy Novgorod to Moscow: Velikiy Novgorod->Saint Petersburg->Moscow\n";
			Assert::AreEqual(matrix_floid_uorshell->Ford_Bellman(city_Start, city_End), cur);
		}
		TEST_METHOD(TestExampleWayIsNotAvaible)
		{
			ifstream input("d:\\Учеба\\АиСд\\FordBellman\\UnitTestFordBellman\\input2.txt");
			List<string>* list_fly = new List<string>();
			string city_Start = "Velikiy Novgorod";
			string city_End = "Lipetsk";
			InputDataFromFile(list_fly, input);
			Matrix* matrix_floid_uorshell = new Matrix(list_fly);
			string cur = "This route can't be built, try waiting for the flight schedule for tomorrow!";
			Assert::AreEqual(matrix_floid_uorshell->Ford_Bellman(city_Start, city_End), cur);
		}
		TEST_METHOD(TestExampleOneFlight)
		{
			ifstream input("d:\\Учеба\\АиСд\\FordBellman\\UnitTestFordBellman\\input3.txt");
			List<string>* list_fly = new List<string>();
			string city_Start = "Saint Petersburg";
			string city_End = "Moscow";
			InputDataFromFile(list_fly, input);
			Matrix* matrix_floid_uorshell = new Matrix(list_fly);
			string cur = "The best route for the price: 10.000000\nWay from Saint Petersburg to Moscow: Saint Petersburg->Moscow\n";
			Assert::AreEqual(matrix_floid_uorshell->Ford_Bellman(city_Start, city_End), cur);
		}
		TEST_METHOD(TestExampleOneFlightWithNoReturnRoute)
		{
			ifstream input("d:\\Учеба\\АиСд\\FordBellman\\UnitTestFordBellman\\input4.txt");
			List<string>* list_fly = new List<string>();
			string city_Start = "Moscow";
			string city_End = "Saint Petersburg";
			InputDataFromFile(list_fly, input);
			Matrix* matrix_floid_uorshell = new Matrix(list_fly);
			string cur = "This route can't be built, try waiting for the flight schedule for tomorrow!";
			Assert::AreEqual(matrix_floid_uorshell->Ford_Bellman(city_Start, city_End), cur);
		}
	};
}
