/*
 * recursion.h
 *
 *  Created on: Jan 2, 2016
 *      Author: alessandroerta
 */

#ifndef RECURSION_H_
#define RECURSION_H_

#include "tree.h"
#include <list>
#include <vector>
#include <utility>

/**
 * count the ways to rump up N steps with 1, 2, 3 or a combination
 * of them, steps at a time.
 */
int countWays(int n);
int countWaysOpt(int n);

/**
 * Return the path from the upper left corner (0,0)
 * to the bottom right corner (r,c) of a rxc matrix
 */

std::list<std::pair<int,int> > findPath(std::vector<std::vector<bool> >);
bool findPath(std::vector<std::vector<bool> >, int right, int down, std::list<std::pair<int,int> > &path);
std::list<std::pair<int,int> > findPathOpt(std::vector<std::vector<bool> >);
bool findPathOpt(std::vector<std::vector<bool> >, std::vector<std::vector<bool> > &visited,
		int right, int down, std::list<std::pair<int,int> > &path);
/**
 * Return all the sets of a set
 */
std::list<std::vector<int> > powerSets(std::vector<int> set);
void powerSets(std::list<int> set, std::list<std::vector<int> > &pset);
std::list<std::vector<int> > addToPset(std::list<std::vector<int> > pset, int val);

/**
 * Multiply without using a *
 */

unsigned int multiply(unsigned int a, unsigned int b);

/**
 * Calculate and return all permutation of one array
 */

std::vector<std::vector<int> > permute(std::vector<int> in);
void permute(std::vector<int> &in, std::vector<int> &out,
			 std::vector<bool> &used, std::vector<std::vector<int> > &permutations);

/**
 * Return the minimal binary tree from a sorted array
 */
BinaryNode<int>* minimalTree(std::vector<int> array, int start, int end);



#endif /* RECURSION_H_ */
