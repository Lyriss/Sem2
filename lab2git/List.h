#pragma once
using namespace std;
template<class T>
class List
{
private:
	class Node {
	public:
		Node(T data = T(), Node* Next = NULL) {
			this->data = data;
			this->Next = Next;
		}
		Node* Next;
		T data;
	};
public:
	void push_back(T obj) { // добавление в конец списка bc
		if (head != NULL) {
			this->tail->Next = new Node(obj);
			tail = tail->Next;
		}
		else {
			this->head = new Node(obj);
			this->tail = this->head;
		}
		Size++;
	}
	void push_front(T obj) { // добавление в начало списка bc
		if (head != NULL) {
			Node* current = new Node;
			current->data = obj;
			current->Next = this->head;
			this->head = current;
		}
		else {
			this->head = new Node(obj);
		}
		this->Size++;
	}
	void pop_back() { // удаление последнего элемента bc
		if (head != NULL) {
			Node* current = head;
			while (current->Next != tail)//то есть ищем предпоследний
				current = current->Next;
			delete tail;
			tail = current;
			tail->Next = NULL;
			Size--;
		}
		else throw std::out_of_range("out_of_range");
	}
	void pop_front() { // удаление первого элемента bc-+
		if (head != NULL) {
			Node* current = head;
			head = head->Next;
			current->Next = NULL;
			delete current;
			Size--;
		}
		else throw std::out_of_range("out_of_range");
	}
	void insert(T obj, size_t k) {// добавление элемента по индексу (вставка перед элементом, который был ранее доступен по этому индексу) bc
		if (k >= 0 && this->Size > k) {
			if (this->head != NULL) {
				if (k == 0)
					this->push_front(obj);
					else
					{
						Node* current = new Node;//для добавления элемента
						Node* current1 = head;//для поиска итого элемента
						for (int i = 0; i < k - 1; i++) {
							current1 = current1->Next;
						}
						current->data = obj;
						current->Next = current1->Next;//переуказывает на след элемент
						current1->Next = current;
						Size++;
					}
			}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}
	T at(size_t k) {// получение элемента по индексу bc
		if (this->head != NULL && k >= 0 && k <= this->Size - 1) {
			if (k == 0)
				return this->head->data;
			else
				if (k == this->Size - 1)
					return this->tail->data;
				else
				{
					Node* current = head;
					for (int i = 0; i < k; i++) {
						current = current->Next;
					}
					return current->data;
				}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}
	void remove(int k) { // удаление элемента по индексу bc
		if (head != NULL && k >= 0&&k<=Size-1) {
			if (k == 0) this->pop_front();
			else
				if (k == this->Size - 1) this->pop_back();
				else
					if (k != 0) {
						Node* current = head;
						for (int i = 0; i < k - 1; i++) {//переходим на предэлемент
							current = current->Next;
						}

						Node* current1 = current->Next;
						current->Next = current->Next->Next;
						delete current1;
						Size--;
					}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}
	size_t get_size() { // получение размера списка bc
		return Size;
	}
	void print_to_console() { // вывод элементов списка в консоль через разделитель, не использовать at bc
		if (this->head != NULL) {
			Node* current = head;
			for (int i = 0; i < Size; i++) {
				cout << current->data << ' ';
				current = current->Next;
			}
		}
	}
	void clear() { // удаление всех элементов списка
		if (head != NULL) {
			Node* current = head;
			while (head != NULL) {
				current = current->Next;
				delete head;
				head = current;
			}
			Size = 0;
		}
	}
	void set(size_t k, T obj)  // замена элемента по индексу на передаваемый элемент 
	{
		if (this->head != NULL && this->get_size() >= k && k >= 0) {
			Node* current = head;
			for (int i = 0; i < k; i++) {
				current = current->Next;
			}
			current->data = obj;
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}
	void sort() {
		T* array = new T[this->Size];
		Node* cur = head;
		int i = 0;
		while (cur != NULL) {
			array[i] = cur->data;
			cur = cur->Next;
			i++;
		}
		QuickSort(array, 0, this->Size - 1);
		cur = head;
	    i = 0;
		while (cur != NULL) {
			cur->data=array[i];
			cur = cur->Next;
			i++;
		}
	}
	bool isEmpty() { // проверка на пустоту списка bc
		return (bool)(head);
	}
	void reverse() { // меняет порядок элементов в списке
		int Counter = Size;
		Node* HeadCur = NULL;
		Node* TailCur = NULL;
		for (int j = 0; j <Size; j++) {
			if (HeadCur != NULL) {
				if(head!=NULL&&head->Next==NULL){
					TailCur->Next = head;
					TailCur = head;
					head = NULL;
				}
				else {
						Node * cur = head;
					for (int i = 0; i < Counter - 2; i++)
						cur = cur->Next;
					TailCur->Next = cur->Next;
					TailCur = cur->Next;
					cur->Next = NULL;
					tail = cur;
					Counter--;
				}
			}
			else {
				HeadCur = tail;
				TailCur = tail;
				Node* cur = head;
				for (int i = 0; i < Size - 2; i++)
					cur = cur->Next;
				tail = cur;
				tail->Next = NULL;
				Counter--;
			}
		}
		head = HeadCur;
		tail = TailCur;
	}
public:
	List(Node* head = NULL, Node* tail = NULL, int Size = 0) :head(head), tail(tail), Size(Size) {}
	~List() {
		if (head != NULL) {
			this->clear();
		}
	};
private:
	Node* head;
	Node* tail;
	int Size;
	void swap(T& a, T& b) {
		T c = a;
		a = b;
		b = c;
	}
	void QuickSort(T* mas, int first, int last)
	{
		T mid;
		int f = first, l = last;
		mid = mas[(f + l) / 2];
		do
		{
			while (mas[f] < mid) f++;
			while (mas[l] > mid) l--;
			if (f <= l)
			{
				swap(mas[f], mas[l]);
				f++;
				l--;
			}
		} while (f < l);
		if (first < l) QuickSort(mas, first, l);
		if (f < last) QuickSort(mas, f, last);
	}
};
