#pragma once
#include <iostream>
using namespace std;



template <typename T>
class LinkedList {
	struct Node;
public:
	// Behaviors
	void printForward() const {
		Node* temp = head;
		for (int i = 1; i<count; i++){
			std::cout<<temp->data;
			temp = temp->next;
		}

	}
	void printReverse() const {
		Node* temp = tail;
		for (int i=count-2; i>-1;i--) {
			std::cout<<temp->data;
			temp = temp->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const{return count;}
	Node* getHead(){return head;}
	const Node* getHead() const{return head;}
	Node* getTail(){return tail;}
	const Node* getTail() const{return tail;}

	// Insertion
	void addHead(const T& data) {
		Node* temp = new Node{data,nullptr,head};
		if (head==nullptr) {
			tail = temp;
		}
		else
			head->prev = temp;
		head = temp;
		temp = nullptr;
		count++;
	}
	void addTail(const T& data) {
		Node* temp = new Node{data,tail,nullptr};
		if (tail == nullptr) {
			head = temp;
		}
		else {
			tail->next = temp;
		}

		tail = temp;
		temp = nullptr;
		count++;
	}

	// Removal
	bool removeHead() {
		if (count == 0) {
			return false;
		}

		Node* temp = head;
		head = nullptr;
		delete head;
		head = temp->next;
		temp = nullptr;
		count--;
		return true;
	}
	bool removeTail() {
		if (count==0) {
			return false;
		}
		(tail->prev)->next = nullptr;
		Node* temp = tail;
		delete tail;
		tail = temp->prev;
		temp = nullptr;
		count--;
		return true;
	}
	void clear() {
		if (count==0) {
			head = nullptr;
			tail = nullptr;
			return;
		}
		Node* temp = head;
		while (head!=nullptr){
			removeHead();
			temp = temp->next;
		}
		head = nullptr;
		tail = nullptr;
		count = 0;

	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept {
		if (this == &other) {
			return(*this);
		}
		this->clear();
		this->head = other.head;
		this->tail = other.tail;
		this->count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return(*this);
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) {
			return(*this);
		}
		LinkedList* temp = new LinkedList();

		temp->count = rhs.count;
		// if (rhs.count==0) {
		//
		// 	return(*this); maybe useful later?
		// }
		temp->addHead(rhs.head->data);

		Node* rhsTempNode = rhs.head;
		for (int i = 1; i<count;i++) {
			temp->addTail(rhsTempNode->data);
			rhsTempNode = rhsTempNode->next;
		}
		this->clear();
		this->head = temp->head;
		temp = nullptr;
		return(*this);
	}


	// Construction/Destruction
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list) {

		this->head = list.head;
		this->tail = list.head;
		this->count = list.count;
		this->addHead(list.head->data);

		Node* rhsTempNode = list.head->next;
		for (int i = 1; i<count;i++) {
			this->addTail(rhsTempNode->data);
			rhsTempNode = rhsTempNode->next;
		}

	}
	LinkedList(LinkedList<T>&& other) noexcept {
		this->head = other.head;
		this->tail = other.tail;
		this->count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {clear();}

private:
	// Stores pointers to first and last nodes and count

	struct Node {
		T data;
		Node* prev;
		Node* next;
	};

	Node* head;
	Node* tail;
	unsigned int count;

};


