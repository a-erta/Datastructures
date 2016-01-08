/*
 * utils.h
 *
 *  Created on: Jan 4, 2016
 *      Author: alessandroerta
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include <vector>
#include "tree.h"


/**
 * Print out a vector
 */
void printVector(std::vector<int> in);

/**
 * Build an array of ints from an array of bynaryNode<int>
 */
std::vector<int> buildIntArray(std::vector<BinaryNode<int>*> a);

/**
 * Return the i-th bit of an int n
 */

bool getBit(int n, int i);

/**
 * Compute the longest sequence of 1s with at most one 0 in the between
 */

int longestSequence(int n);

/**
 * Return the number of ones in a int
 */

int numOnes(int n);

/**
 * Check if the machine is little endian
 */
int isLittleEndian() ;

#endif /* UTILS_H_ */
