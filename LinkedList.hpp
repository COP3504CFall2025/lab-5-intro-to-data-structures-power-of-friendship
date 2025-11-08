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
		for (int i = 0; i<count; i++){
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
		else {
			head->prev = temp;
			temp->next = head;
		}
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
		if (count == 1) {
			delete head;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		}

		Node* temp = head;
		head = temp->next;
		head->prev = nullptr;
		delete temp;
		temp = nullptr;
		count--;
		return true;
	}
	bool removeTail() {
		if (count==0) {
			return false;
		}
		if (count == 1) {
			delete tail;
			head = nullptr;
			tail = nullptr;
			count--;
			return true;
		}

		Node* temp = tail;
		tail = temp->prev;
		tail->next = nullptr;
		delete temp;
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
		while (head!=nullptr){
			removeHead();
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

		// if (rhs.count==0) {
		//
		// 	return(*this); maybe useful later?
		// }
		Node* temp = new Node{rhs.head->data,nullptr,nullptr};
		Node* tempHead = temp;
		// tail = head;

		Node* rhsTempNode = rhs.head;
		for (int i = 1; i<rhs.count;i++) {
			rhsTempNode = rhsTempNode->next;
			temp->next = new Node(rhsTempNode->data, temp, nullptr);
			temp = temp->next;
		}
		this->clear();
		this->head = tempHead;
		this->tail = temp;
		this->count = rhs.count;
		temp = nullptr;
		tempHead = nullptr;
		return(*this);
	}


	// Construction/Destruction
	LinkedList() {
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list) {
		head = nullptr;
		tail = nullptr;
		count = 0;
		if (list.count == 0) {
			return;
		}


		this->addHead(list.head->data);
		this->tail = this->head;

		Node* rhsTempNode = list.head;
		for (int i = 1; i<list.count;i++) {
			rhsTempNode = rhsTempNode->next;
			addTail(rhsTempNode->data);
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


