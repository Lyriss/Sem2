#include "pch.h"
#include "CppUnitTest.h"
#include"..//List.h"
#include"..//Map.h"
#include"..//Hoffman.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestForHoffmanalgorithmcoding
{
	TEST_CLASS(UnitTestForHoffmanalgorithmcoding)
	{
	public:
			TEST_METHOD(TestCodingHoffman_different_symbol_words)
			{
				string str = "Hello";//
				string coding_str;
				Tree_Hoffman* Tree_Hoffman_tree = new Tree_Hoffman(str);
				Map<char, string>* hoffman = Tree_Hoffman_tree->get_tree_with_code();
				int counter = 0;
				List<Pair<char, int>>* list_symbol = Tree_Hoffman_tree->get_list_symbol();
				for (int i = 0; i < str.size(); i++)
					coding_str += hoffman->find(str[i]);
				Assert::AreEqual(coding_str, string("1011100110"));
			}
			TEST_METHOD(TestCodingHoffman_same_symbol_words)
			{
				string str = "fff";//
				string coding_str;
				Tree_Hoffman* Tree_Hoffman_tree = new Tree_Hoffman(str);
				Map<char, string>* hoffman = Tree_Hoffman_tree->get_tree_with_code();
				int counter = 0;
				List<Pair<char, int>>* list_symbol = Tree_Hoffman_tree->get_list_symbol();
				for (int i = 0; i < str.size(); i++)
					coding_str += hoffman->find(str[i]);
				Assert::AreEqual(coding_str, string("000"));
			}
			TEST_METHOD(TestCodingHoffman_text)
			{
				string str = "it is string";//
				string coding_str;
				Tree_Hoffman* Tree_Hoffman_tree = new Tree_Hoffman(str);
				Map<char, string>* hoffman = Tree_Hoffman_tree->get_tree_with_code();
				int counter = 0;
				List<Pair<char, int>>* list_symbol = Tree_Hoffman_tree->get_list_symbol();
				for (int i = 0; i < str.size(); i++)
					coding_str += hoffman->find(str[i]);
				Assert::AreEqual(coding_str, string("101110010110001101110111100110010"));
			}
	};
}
