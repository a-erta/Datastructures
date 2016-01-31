/*
 * sorting.h
 *
 *  Created on: Dec 27, 2015
 *      Author: alessandroerta
 */

#ifndef SORTING_H_
#define SORTING_H_

#include <vector>
#include "comparators.h"
#include "heap.h"

template <class T>
class Sorting {
	static void swap(std::vector<T> &toSort, int i, int j);
	static void quicksort(std::vector<T> &toSort, Comparator<T> *comp, int left, int right);
	static int findSmallestIndex(std::vector<T> data, int start, Comparator<T> *comp);
	static std::vector<T> _mergesort(std::vector<T> data, Comparator<T> *comp);
	static std::vector<T> merge(std::vector<T> left, std::vector<T> right, Comparator<T> *comp);
public:
	static void quicksort(std::vector<T> &toSort, Comparator<T> *comp);
	static void selectionSort(std::vector<T> &toSort, Comparator<T> *comp);
	static void mergesort(std::vector<T> &toSort, Comparator<T> *comp);
	static void heapsort(std::vector<T> &toSort, Comparator<T> *comp);
};

template <class T>
void Sorting<T>::swap(std::vector<T> &toSort, int i, int j) {
	if (i >= toSort.size() || j >= toSort.size()) return;
	T tmp = toSort[i];
	toSort[i] = toSort[j];
	toSort[j] = tmp;
}

template <class T>
void Sorting<T>::selectionSort(std::vector<T> &toSort, Comparator<T> *comp) {
	for (int start = 0; start < toSort.size() - 1; ++start) {
		swap(toSort, start, findSmallestIndex(toSort, start, comp));
		if (start % 10000 == 0)
			std::cout << (double(start) / double(toSort.size())) * 100 << "%" << std::endl;
	}
}

template <class T>
int Sorting<T>::findSmallestIndex(std::vector<T> data, int start, Comparator<T> *comp) {
	T val = data[start];
	for ( int i = start + 1; i < data.size(); i++ ) {
		if (comp->compare(val, data[i])) {
			val = data[i];
			start = i;
		}
	}
	return start;
}

template <class T>
std::vector<T> Sorting<T>::merge(std::vector<T> left, std::vector<T> right, Comparator<T> *comp) {
	std::vector<T> ret = std::vector<T>(left.size() + right.size());
	int lind = 0;
	int rind = 0;
	int i = 0;
	while (lind < left.size() && rind < right.size()) {
		if (comp->compare(left[lind], right[rind]))
			ret[i++] = right[rind++];
		else
			ret[i++] = left[lind++];
	}

	while (lind < left.size())
		ret[i++] = left[lind++];

	while (rind < right.size())
		ret[i++] = right[rind++];

	return ret;

}

template <class T>
void Sorting<T>::mergesort(std::vector<T> &toSort, Comparator<T> *comp) {
	toSort = _mergesort(toSort, comp);
}

template <class T>
std::vector<T> Sorting<T>::_mergesort(std::vector<T> data, Comparator<T> *comp) {
	if (data.size() < 2) return data;
	int mid = data.size() / 2;
	typename std::vector<T>::const_iterator first = data.begin();
	typename std::vector<T>::const_iterator midI = data.begin() + mid;
	std::vector<T> left(first, midI);
	std::vector<T> right(midI, data.end());

	left = _mergesort(left, comp);
	right = _mergesort(right, comp);

	return merge(left, right, comp);
}


template <class T>
void Sorting<T>::quicksort(std::vector<T> &toSort, Comparator<T> *comp) {
	quicksort(toSort, comp, 0, toSort.size() - 1);
}

template <class T>
void Sorting<T>::quicksort(std::vector<T> &toSort, Comparator<T> *comp, int left, int right) {
	T pivotValue = toSort[ (right + left) / 2 ];
	int i = left;
	int j = right;

	while (i <= j) {
		// find the leftmost value greater than or equal to pivot
		while (comp->compare(pivotValue, toSort[i])) i++;
		// find the rightmost value smaller than or equal to pivot
		while (comp->compare(toSort[j], pivotValue)) j--;

		if (i <= j) {
			swap(toSort, i, j);
			i++;
			j--;
		}
	}

	// apply the algorithm recursively

	if ( left < j ) quicksort(toSort, comp, left, j);
	if ( i < right ) quicksort(toSort, comp, i, right);
}

template <class T>
void Sorting<T>::heapsort(std::vector<T> &toSort, Comparator<T> *comp) {
	Heap<T> heap(Heap<T>::MAX_HEAP, false, comp);
	heap.fromArray(toSort);
	heap.heapSort();
	toSort = heap.toArray();
}


#endif /* SORTING_H_ */
