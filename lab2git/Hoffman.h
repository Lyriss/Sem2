#pragma once
#include"List.h"
#include"Map.h"
#include"Pair.h"
#include<string>
class Tree_Hoffman
{
	class Node {
	public:
		Node(Pair<char, int> value = Pair<char, int>(), Node* left = NULL, Node* right = NULL) :value(value), left(left), right(right) {}
		Pair<char, int> value;
		Node* left;
		Node* right;
	};
public:
	~Tree_Hoffman() {
		this->clear_tree(Top);
	}
	Tree_Hoffman(string str) {
		Map<char, int>* map_symbol = new Map<char, int>();
		list_symbol = new List<Pair<char, int>>();
		for (int i = 0; i < str.size(); i++) {
			if (!map_symbol->find_is(str[i]))//if the symbol is not in the list then add the value to the symbol map otherwise increase the number
				map_symbol->insert(str[i], 1);
			else
				map_symbol->increment_value(str[i]);
		}
		 list_symbol= map_symbol->get_pairs();
		map_symbol->clear();
		list_symbol->sort();		
		///////////////////////////////////////////////////////////////////////////building the encoding tree
		List<Node>* list_for_build_tree = new List<Node>();
		for (int i = 0; i < list_symbol->get_size(); i++)
			list_for_build_tree->push_back(Node(list_symbol->at(i)));
		build_tree(list_for_build_tree);
		///////////////////////////////////////////////////////////////////////////
	}
	List<Pair<char, int>>* get_list_symbol() {
		return list_symbol;
	}
	Map<char, string>*& get_tree_with_code() {
		Map<char, string>* hoffman = new Map<char, string>();
		string cur;
		fill_tree_with_code(hoffman, Top, cur);
		return hoffman;
	}
	string Decoding_hoffman_tree(string& coding_str) {
		string decoding_str;
		int pos = 0;
		Decoding(Top, coding_str, decoding_str, pos);
		return decoding_str;
	}
private:
	void Decoding(Node* root, string& coding_str, string& decoding_str, int& position) {
		if (coding_str.size() > position) {
			while (root->right != NULL && root->left != NULL) {
				if (coding_str[position] == '0')
					root = root->left;
				else
					root = root->right;
				position++;
			}
			decoding_str += root->value.first;
			if (Top->left == NULL && Top->right == NULL)
				position++;
			Decoding(Top, coding_str, decoding_str, position);
		}
	}
	void build_tree(List<Node>*& list_for_build_tree) {
		Top = NULL;
		if (list_for_build_tree->get_size() > 1) {
			while (list_for_build_tree->get_size() != 0) {
				Node* cur = new Node();
				cur->left = new Node(list_for_build_tree->at(0));
				cur->right = new Node(list_for_build_tree->at(1));
				cur->value.second = list_for_build_tree->at(0).value.second + list_for_build_tree->at(1).value.second;
				list_for_build_tree->pop_front();
				list_for_build_tree->pop_front();
				int i = 0;
				for (; i < list_for_build_tree->get_size() && list_for_build_tree->at(i).value.second < cur->value.second; i++);
				if (list_for_build_tree->get_size() != 0 && list_for_build_tree->get_size() != i)
					list_for_build_tree->insert(*cur, i);
				else
					if (list_for_build_tree->get_size() == i && list_for_build_tree->get_size() != 0)
						list_for_build_tree->push_back(*cur);
				if (list_for_build_tree->get_size() == 0) {
					Top = cur;
				}
			}
		}
		else {
			Top = new Node(Pair<char, int>(list_for_build_tree->at(0).value.first, list_for_build_tree->at(0).value.second));
		}
		//////////////////////////////////////////////////////////////////////////
	}
	void fill_tree_with_code(Map<char, string>* hoffman, Node* root, string cur) {//filling in the code tree
		if (Top->left != NULL && Top->right != NULL) {
			if (root->left != NULL && root->right != NULL) {
				fill_tree_with_code(hoffman, root->left, cur + '0');
				fill_tree_with_code(hoffman, root->right, cur + '1');
			}
			else
			{
				hoffman->insert(root->value.first, cur);
			}
		}
		else {
			hoffman->insert(root->value.first, cur + '0');
		}
	}
	void clear_tree(Node* tree) {
		if (tree != NULL) {
			clear_tree(tree->left);
			clear_tree(tree->right);
			delete tree;
		}
	}
	Node* Top;
	List<Pair<char, int>>* list_symbol;
};