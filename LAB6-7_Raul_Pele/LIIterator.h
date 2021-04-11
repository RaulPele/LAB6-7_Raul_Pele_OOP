#pragma once
#include "LinkedList.h"
#include "Node.h"

template <typename TElement>
class LIIterator {
private:
	template<typename> friend class LinkedList;

	//fields
	const LinkedList<TElement>& list;
	Node<TElement>* current;
	
public:
	//constructors/destructors
	LIIterator() : current(nullptr), list(nullptr) {}
	LIIterator(const LinkedList<TElement>& list) :list(list) { current = list.head; };

	//interface
	void next();
	TElement& value() const;
	bool valid() const;

	//operators
	bool operator!=(const LIIterator<TElement>& it2);
	bool operator==(const LIIterator<TElement>& it2);
	TElement& operator*();
	LIIterator<TElement>& operator++();
};

template <typename TElement>
void LIIterator<TElement>::next(){
	this->current = this->current->next;
}

template <typename TElement>
bool LIIterator<TElement>::valid() const{
	if (this->current != nullptr) {
		return true;
	}
	return false;
}

template <typename TElement>
TElement& LIIterator<TElement>::value() const {
	return this->current->getData();
}

template <typename TElement>
bool LIIterator<TElement>::operator==(const LIIterator<TElement>& it2) {
	if (this->current != it2->current) {
		return false;
	}
	return true;
}

template <typename TElement>
bool LIIterator<TElement>::operator!=(const LIIterator<TElement>& it2) {
	if (this->current != it2.current) {
		return true;
	}
	return false;
}

template <typename TElement>
LIIterator<TElement>& LIIterator<TElement>::operator++() {
	this->next();
	return *this;
}

template <typename TElement>
TElement& LIIterator<TElement>::operator*() {

	return this->value();
}