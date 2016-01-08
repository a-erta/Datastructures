/*
 * utils.cpp
 *
 *  Created on: Jan 4, 2016
 *      Author: alessandroerta
 */

#include "utils.h"

void printVector(std::vector<int> in) {
	for (int i = 0; i < in.size(); i++)
		std::cout << in[i] << " ";
	std::cout << std::endl;
}

std::vector<int> buildIntArray(std::vector<BinaryNode<int>*> a) {
	std::vector<int> ret;
	for (int i = 0; i < a.size(); i++) {
		ret.push_back(a.at(i)->data);
	}
	return ret;
}

bool getBit(int n, int i) {
	return ((n & (1 << i)) != 0);
}

int longestSequence(int n) {
	int max = 0, curr = 0, last = 0;
	bool first = true;
	for ( int i = 0; i < 32; i++ ) {
		if(getBit(n, i) == 1) {
			curr++;
		} else {
			if (first && curr != 0) {
				first = false;
				curr++;
				last = i;
			} else if (!first) {
				i = last;
				if ( max < curr ) max = curr;
				std::cout << "SEQ: " << curr << " last: " << i << std::endl;
				curr = 0;
				first = true;
			}
		}
	}
	if ( max < curr ) max = curr;
	return max;
}

// return the number of ones in a binary representation of a number
int numOnes(int n) {
	int num = 0;
	while(n) {
		n &= n-1;
		num++;
	}
	return num;
}

// return the endianess of the machine
int isLittleEndian() {
	union {
		int num;
		char first;
	} endian;
	endian.num = 1;
	return endian.first;
}


