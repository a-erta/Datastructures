/*
 * comparators.h
 *
 *  Created on: Jan 31, 2016
 *      Author: alessandroerta
 */

#ifndef COMPARATORS_H_
#define COMPARATORS_H_

template <class T>
class Comparator {
public:
	Comparator(){};
	virtual bool compare(T a, T b) = 0;
	virtual ~Comparator(){};
};

class IntComparator : public Comparator<int> {
	int ordering;
public:
	enum ORDER {ASC, DESC};
	IntComparator() : ordering(ORDER::ASC) {}
	IntComparator(ORDER ord) { ordering = ord; }
	bool compare(int a, int b) { return (ordering == ORDER::ASC) ? a > b : b > a; }
	~IntComparator(){}
};


#endif /* COMPARATORS_H_ */
