/*
 * heap.h
 *
 *  Created on: Jan 31, 2016
 *      Author: alessandroerta
 */

#ifndef HEAP_H_
#define HEAP_H_

#include <cstddef>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <climits>
#include "comparators.h"

template<class T>
class Heap {
	/**
	 * data = [not-used, d1, d2, ..., dn]
	 */
	std::vector<T> data;
	Comparator<T> *comp;
	bool heap;
	int LEFT(int i) { return 2*i; }
	int RIGHT(int i) { return 2*i + 1; }
	int PARENT(int i) { return i / 2; }
	void maxHeapify(int i, int size = -1);
	void swap(int a, int b);
public:
	enum HeapType {MAX_HEAP, MIN_HEAP};
	Heap() : comp(new IntComparator()), heap_type(MAX_HEAP), heap(false) {}
	Heap(HeapType heap_type, bool heap, Comparator<T> *comp = new IntComparator());
	HeapType heapType() { return heap_type; }
	void add(T val);
	void heapify();
	std::vector<T> toArray();
	void fromArray(std::vector<T> in);
	// Note: the internal array is no longer a heap but it's sorted!
	void heapSort();
	bool isHeap() { return heap; }

private:
	HeapType heap_type;
};

template <class T>
Heap<T>::Heap(HeapType ht, bool h, Comparator<T> *c) {
	this->comp = c;
	this->heap_type = ht;
	this->heap = h;
}

template <class T>
void Heap<T>::maxHeapify(int i, int size) {
	size = size == -1 ? this->data.size() : size;
	if (i == 0 || i >= size) return;
	int max = i;
	if ( LEFT(i) <= size &&
			comp->compare(this->data[LEFT(i)], this->data[max]) )
		max = LEFT(i);
	if ( RIGHT(i) <= size &&
			comp->compare(this->data[RIGHT(i)], this->data[max]) )
		max = RIGHT(i);
	if (max != i) {
		swap(i, max);
		maxHeapify(max, size);
	}
}

template <class T>
void Heap<T>::swap(int a, int b) {
	if ( a < this->data.size() && b < this->data.size() ) {
		T tmp = this->data[a];
		this->data[a] = this->data[b];
		this->data[b] = tmp;
	}
}

template <class T>
void Heap<T>::add(T val) {
	this->data.push_back(val);
	this->heapify();
}

template <class T>
void Heap<T>::heapify() {
	for (int i = this->data.size() / 2; i > 0; i--) {
		if (heap_type == MAX_HEAP) {
			this->maxHeapify(i);
		} else { // TODO
		}
	}
	heap = true;
}

template <class T>
void Heap<T>::fromArray(std::vector<T> in) {
	this->data.resize(in.size() + 1);
	std::copy(in.begin(), in.end(), this->data.begin() + 1);
	heapify();
}

template <class T>
std::vector<T> Heap<T>::toArray() {
	std::vector<T> ret(this->data.size() - 1);
	std::copy(this->data.begin() + 1, this->data.end(), ret.begin());
	return ret;
}

template <class T>
void Heap<T>::heapSort() {
	if (! heap) heapify();
	for (int i = this->data.size(); i > 1; i--) {
		swap(1, i);
		this->maxHeapify(1, i-1);
	}
	heap = false;
}



#endif /* HEAP_H_ */
