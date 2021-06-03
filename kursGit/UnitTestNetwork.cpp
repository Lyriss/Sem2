#include "pch.h"
#include "CppUnitTest.h"
#include "../Edmonds_Karp/Network.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestNetwork
{
	TEST_CLASS(UnitTestNetwork)
	{
	public:
		
		TEST_METHOD(TestMethod_Correct_output_for_6_vertexes)
		{
			ifstream input("C:\\tests\\Input1.txt");
			Network Flows(input);
			Assert::AreEqual(Flows.max_flow(), 5);
		}
		TEST_METHOD(TestMethod_Exception_entering_the_first_character) {
			try {
				ifstream input("C:\\tests\\Input2.txt");
				Network Flows(input);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "Error entering the first character in the string or missing a space after it. Check the correctness of the input in the file and correct these errors in the line under the number: 2");
			}
		}
		TEST_METHOD(TestMethod_Exception_entering_the_second_character) {
			try {
				ifstream input("C:\\tests\\Input3.txt");
				Network Flows(input);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "Error entering the second character in the string or missing a space after it. Check the correctness of the input in the file and correct these errors in the line under the number: 2");
			}
		}
		TEST_METHOD(TestMethod_Exception_entering_the_third_number_Flows) {
			try {
				ifstream input("C:\\tests\\Input4.txt");
				Network Flows(input);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "Error entering the third character (bandwidth) in the string or the presence of a space after it.Please note that the bandwidth cannot be negative. Check that you entered the file correctly and correct these errors in the line number: 2");
			}
		}
		TEST_METHOD(TestMethod_Exception_empty_string) {
			try {
				ifstream input("C:\\tests\\Input5.txt");
				Network Flows(input);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "A data-entry error. Check the correctness of the input in the file and correct these errors in the line under the number: 2");
			}
		}
		TEST_METHOD(TestMethod_Correct_output_for_6_vertexes_and_edge_from_source_to_sink)
		{
			ifstream input("C:\\tests\\Input6.txt");
			Network Flows(input);
			Assert::AreEqual(Flows.max_flow(), 25);
		}
		TEST_METHOD(TestMethod_Correct_output_for_2_vertexes_edges_from_source_to_sink)
		{
			ifstream input("C:\\tests\\Input7.txt");
			Network Flows(input);
			Assert::AreEqual(Flows.max_flow(), 20);
		}
		TEST_METHOD(TestMethod_Exception_there_is_a_path_from_the_vertex_to_itself) {
			try
			{
				ifstream input("C:\\tests\\Input8.txt");
				Network Flows(input);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "The path from the vertex to itself is impossible in the string under the number: 2");
			}
		}
		TEST_METHOD(TestMethod_Сorrect_output_for_20_vertexes)
		{
			ifstream input("C:\\tests\\Input9.txt");
			Network Flows(input);
			Assert::AreEqual(Flows.max_flow(), 19);
		}
		TEST_METHOD(TestMethod_Exception_missing_is_source) {
			try
			{
				ifstream input("C:\\tests\\Input10.txt");
				Network Flows(input);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "Source is missing");
			}
		}
		TEST_METHOD(TestMethod_Exception_missing_is_sink) {
			try
			{
				ifstream input("C:\\tests\\Input11.txt");
				Network Flows(input);
			}
			catch (exception& ex) {
				Assert::AreEqual(ex.what(), "Sink is missing");
			}
		}
		TEST_METHOD(TestMethod_No_path)
		{
			ifstream input("C:\\tests\\Input12.txt");
			Network Flows(input);
			Assert::AreEqual(Flows.max_flow(), 0);
		}
	};
}
