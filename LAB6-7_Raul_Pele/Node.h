#pragma once
#include "LinkedList.h"

template<typename TElement> class Node {
private:
	TElement data;
	template <typename> friend class LinkedList;

public:
	Node(TElement data, Node* next): data(data), next(next) {};
	TElement& getData();
	Node* getNext() const;
	Node* next;

};

template<typename TElement>
TElement& Node<TElement>::getData() {
	return this->data;
}

template<typename TElement>
Node<TElement>* Node<TElement>::getNext() const {
	return this->next;
}

