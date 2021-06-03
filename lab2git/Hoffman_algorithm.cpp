#include<iostream>
#include"Map.h"
#include<string>
#include"Hoffman.h"
using namespace std;



int main() {
	string str;//
	string coding_str;
	setlocale(LC_ALL, "RU");
	cout << "Введите строку которую хотите закодировать: ";
	getline(cin, str);
	Tree_Hoffman* Tree_Hoffman_tree = new Tree_Hoffman(str);
	Map<char, string>* hoffman = Tree_Hoffman_tree->get_tree_with_code();
	int counter = 0;
	List<Pair<char, int>>* list_symbol = Tree_Hoffman_tree->get_list_symbol();
	for (int i = 0; i < list_symbol->get_size(); i++)
		cout << '{' << list_symbol->at(i).first << '}' << "==" << '{' << hoffman->find(list_symbol->at(i).first) << "} с частотой: " << list_symbol->at(i).second << endl;
	cout << "старая строка: " << str << endl;
	cout << "новая строка: ";
	for (int i = 0; i < str.size(); i++) {
		coding_str += hoffman->find(str[i]);
		cout << hoffman->find(str[i]);
		counter += hoffman->find(str[i]).size();
	}
	cout << endl << "кол-во сиволов: " << counter << endl;

	string decoding_str = Tree_Hoffman_tree->Decoding_hoffman_tree(coding_str);
	cout << "Коэфициент сжатия: x" << (((double)(decoding_str.size() * 8) / (coding_str.size())));
	delete Tree_Hoffman_tree;
	return 0;
}