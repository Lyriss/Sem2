#include<iostream>
using namespace std;
template<typename T>
class List
{
private:
	class Node {
	public:
		Node(T data = T(), Node* Next = NULL) 
		{
			this->data = data;
			this->Next = Next;
		}
		Node* Next;
		T data;
	};

public:
	void push_back(T obj)  // add to the end of the list
	{
		if (head != NULL) 
		{
			this->tail->Next = new Node(obj);
			tail = tail->Next;
		}
		else {
			this->head = new Node(obj);
			this->tail = this->head;
		}
		Size++;
	}

	void insert(T obj, size_t k) // adding an item by index (insert before an item that was previously available by this index) 
	{
		if (k >= 0 && this->Size > k) 
		{
			if (this->head != NULL) 
			{
				if (k == 0)
					this->push_front(obj);
				else
					if (k == this->Size - 1)
						this->push_back(obj);
					else
					{
						Node* current = new Node;//to add an element
						Node* current1 = head;//to search for the total element
						for (int i = 0; i < k - 1; i++) 
						{
							current1 = current1->Next;
						}
						current->data = obj;
						current->Next = current1->Next;//points to the next element
						current1->Next = current;
						Size++;
					}
			}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}

	T at(size_t k) {// getting an item by index 
		if (this->head != NULL && k >= 0 && k <= this->Size - 1) 
		{
			if (k == 0)
				return this->head->data;
			else
				if (k == this->Size - 1)
					return this->tail->data;
				else
				{
					Node* current = head;
					for (int i = 0; i < k; i++) 
					{
						current = current->Next;
					}
					return current->data;
				}
		}
		else {
			throw std::out_of_range("out_of_range");
		}
	}

	void remove(int k) { // deleting an item by index 
		if (head != NULL && k >= 0 && k <= Size - 1) 
		{
			if (k == 0) this->pop_front();
			else
				if (k == this->Size - 1) this->pop_back();
				else
					if (k != 0) 
					{
						Node* current = head;
						for (int i = 0; i < k - 1; i++) //go to the pre element
						{
							current = current->Next;
						}

						Node* current1 = current->Next;
						current->Next = current->Next->Next;
						delete current1;
						Size--;
					}
		}
		else 
		{
			throw std::out_of_range("out_of_range");
		}
	}

	size_t get_size() { // getting the list size 
		return Size;
	}

	void clear() // deleting all list items
	{
		if (head != NULL) 
		{
			Node* current = head;
			while (head != NULL) 
			{
				current = current->Next;
				delete head;
				head = current;
			}
			Size = 0;
		}
	}

public:
	List(Node* head = NULL, Node* tail = NULL, int Size = 0) :head(head), tail(tail), Size(Size) {}
	~List() 
	{
		if (head != NULL) 
		{
			this->clear();
		}
	};

private:
	Node* head;
	Node* tail;
	int Size;
};