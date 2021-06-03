#include "pch.h"
#include "CppUnitTest.h"
#include"../RedBlackTree/Map.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RedBlackTreeTest
{
	TEST_CLASS(RedBlackTreeTest)
	{
	public:
		TEST_METHOD(GetKeys)
		{
			Map<int, int>* tree = new Map<int, int>();
			tree->insert(8, -1);
			tree->insert(5, -2);
			tree->insert(7, -3);
			tree->insert(11, -4);
			List<int>* list = tree->get_keys();
			int sum = 0;
			for (int i = 0; i < list->get_size(); i++)
				sum += list->at(i);
			Assert::AreEqual(31, sum);
		}
		TEST_METHOD(GetValues)
		{
			Map<int, int>* tree = new Map<int, int>();
			tree->insert(8, -1);
			tree->insert(5, -2);
			tree->insert(7, -3);
			tree->insert(11, -4);
			List<int>* list = tree->get_values();
			int sum = 0;
			for (int i = 0; i < list->get_size(); i++)
				sum += list->at(i);
			Assert::AreEqual(-10, sum);
		}
		TEST_METHOD(InsertAndFind)
		{
			Map<int, int>* tree = new Map<int, int>();
			tree->insert(8, -1);
			tree->insert(5, -2);
			tree->insert(7, -3);
			tree->insert(11, -4);
			Assert::AreEqual(tree->find(8), -1);
		}
		TEST_METHOD(FindExeption)
		{
			try {
				Map<int, int>* tree = new Map<int, int>();
				tree->insert(8, -1);
				tree->insert(5, -2);
				tree->insert(7, -3);
				tree->insert(11, -4);
				tree->find(29);
			}
			catch (std::out_of_range exc) {
				Assert::AreEqual("Key is missing", exc.what());
			}
		}
		TEST_METHOD(Remove)
		{
			try {
				Map<int, int>* tree = new Map<int, int>();
				tree->insert(8, -1);
				tree->insert(5, -2);
				tree->insert(7, -3);
				tree->insert(11, -4);
				tree->remove(8);
				tree->find(8);
			}
			catch (std::out_of_range exc) {
				Assert::AreEqual("Key is missing", exc.what());
			}
		}
		TEST_METHOD(ClearExeption)
		{
			try {
				Map<int, int>* tree = new Map<int, int>();
				tree->insert(8, -1);
				tree->insert(5, -2);
				tree->insert(7, -3);
				tree->insert(11, -4);
				tree->clear();
				tree->printTree();
			}
			catch (std::out_of_range exc) {
				Assert::AreEqual("Tree is empty!", exc.what());
			}
		}
	};
}
