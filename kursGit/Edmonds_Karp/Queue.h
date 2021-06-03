#pragma once
template<typename T>
class Queue
{
public:
	class Node
	{
	public:
		Node(T data = T(), Node* next = NULL):data(data),next(next) {}
		T data;
		Node* next;
	};
	void enqueue(T current){ // adding to the queue
		if (head != NULL) {
			this->tail->next = new Node(current);
			this->tail = this->tail->next;
		}
		else {
			this->head = new Node(current);
			this->tail = head;	
		}
		this->Counter++;
	}
	T dequeue() {// Remove from queue. Returns the deleted item
		if (head != NULL) {
			Node* current = head;
			T cur = head->data;
			head = head->next;
			delete current;
			this->Counter--;
			return cur;
		}else throw std::out_of_range("out_of_range");
	}
	T peek() { //returns an item from the beginning of the queue
		if (head != NULL) {
		return head->data;
		}
		else throw std::out_of_range("out_of_range");
	}
	int get_size() { // returns the number of items in the queue
		return Counter;
	}
	bool empty() {
		if (head != NULL)
			return false;
		else
			return true;
	}
	Queue(Node* head = NULL, Node* tail = NULL, int Counter = 0):head(head),tail(tail),Counter(Counter) {}
	~Queue() {
		while (head != NULL) {
			Node* cur = head->next;
			delete head;
			head = cur;
		}
	}
private:
	Node* head;
	Node* tail;
	int Counter;
};