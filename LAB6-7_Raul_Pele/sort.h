#pragma once
#include "LinkedList.h"
#include "Discipline.h"
#include "compare.h"
#include "LIIterator.h"

LinkedList<Discipline> sort(const LinkedList<Discipline>& list, CompareFunction cmp) {
	LinkedList<Discipline> sorted;
	bool done = false;
	do {
		done = true;
		LIIterator<Discipline> it = list.begin(), it2 = list.begin();
		while (it2.valid()) {
			if (cmp(it.value(), it2.value())) {
				
			}
		}
		
	} while (true);
}