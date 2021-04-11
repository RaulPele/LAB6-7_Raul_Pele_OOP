#pragma once
#include<memory>
#include "Node.h"
#include "LIIterator.h"
#include "compare.h"
using namespace std;

template<typename TElement> class LinkedList {
private:
	template <typename> friend class LIIterator;
	template <typename> friend class Node;
	Node<TElement>* head;

	void destroyList(Node<TElement>* head);

public:
	//constructors/desctructors
	LinkedList(): head(nullptr){}
	LinkedList(const LinkedList<TElement>& other);
	~LinkedList();

	//interface
	void add(const TElement& elem);
	void remove(LIIterator<TElement>& it);
	void sort(CompareFunction cmp, bool reversed);
	unsigned int size() const;
	bool empty() const;

	LIIterator<TElement> begin() const;
	LIIterator<TElement> end() const;

	//operators
	LinkedList<TElement>& operator=(const LinkedList<TElement>& other);
};

template<typename TElement>
LinkedList<TElement>::LinkedList(const LinkedList<TElement>& other):head(nullptr) {
	Node<TElement>* current = other.head;

	while (current != nullptr) {
		this->add(current->getData());
		current = current->next;
	}
}

template<typename TElement>
LinkedList<TElement>& LinkedList<TElement>::operator=(const LinkedList<TElement>& other) {
	if (this->head != nullptr) {
		this->destroyList(this->head);
	}
	this->head = nullptr;

	Node<TElement>* current = other.head;
	while (current != nullptr) {
		this->add(current->getData());
		current = current->next;
	}
	return *this;
}


template<typename TElement>
bool LinkedList<TElement>::empty() const{
	if (this->head == nullptr) {
		return true;
	}
	return false;
}

template<typename TElement>
unsigned int LinkedList<TElement>::size() const{
	if (this->empty()) {
		return 0;
	}

	unsigned int dim = 0;
	Node<TElement>* current = head;
	while (current != nullptr) {
		dim++;
		current = current->next;
	}
	return dim;
}

template<typename TElement>
void LinkedList<TElement>::add(const TElement& elem) {
	Node<TElement>* newElem = new Node<TElement>{ elem, nullptr };

	if (this->head == nullptr) {
		//empty list case
		this->head = newElem;
	}
	else {
		Node<TElement>* current = this->head;
		while (current->next != nullptr) {
			current = current->next;
		}
		current->next = newElem;
	}
}

template<typename TElement>
void LinkedList<TElement>::remove(LIIterator<TElement>& it) {
	//if (!it.valid()) {
	//	//throw exception
	//	return;
	//}
	Node<TElement>* deleted = nullptr;
	if (it.current == this->head) {	
		//remove the first element in the list
		deleted = this->head;
		this->head = this->head->next;
		it.next();
		delete deleted;
	}
	else {
		Node<TElement>* current = this->head;

		while (current->next != it.current && current!=nullptr) {
			current = current->next;
		}
		
		deleted = current->next;
		current->next = it.current->next;

		//delete it.current;
		it.next();
		delete deleted;
	//	it.current = current->next;
	}
}

template<typename TElement>
LIIterator<TElement> LinkedList<TElement>::begin() const{
	return LIIterator<TElement>(*this);
}

template<typename TElement>
LIIterator<TElement> LinkedList<TElement>::end() const {
	LIIterator<TElement> it{ *this };

	while (it.valid()) {
		it.next();
	}

	return it;
}

template<typename TElement>
void LinkedList<TElement>::sort(CompareFunction cmp, bool reversed) {
	bool sorted = false;
	if (this->head == nullptr) {
		return;
	}

	do {
		Node<TElement>* node1 = this->head;
		sorted = true;
		while (node1->next != nullptr) {
			if ((cmp(node1->data, node1->next->data) && reversed == false ) ||
				(!cmp(node1->data, node1->next->data) && reversed == true)) {
				//swap
				TElement aux = node1->data;
				node1->data = node1->next->data;
				node1->next->data = aux;
				sorted = false;
			}
			node1 = node1->next;
		}
	} while (!sorted);
}

template<typename TElement>
void LinkedList<TElement>::destroyList(Node<TElement>* first) {
	if (first == nullptr) {
		return;
	}

	while (first != nullptr) {
		Node<TElement>* prev = first;
		first = first->next;
		delete prev;
	}
	first = nullptr;
}

template<typename TElement>
LinkedList<TElement>::~LinkedList() {
	this->destroyList(this->head);
}