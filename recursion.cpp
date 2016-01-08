/*
 * recursion.cpp
 *
 *  Created on: Jan 2, 2016
 *      Author: alessandroerta
 */
#include "recursion.h"
#include <iostream>

int countWays(int n) {
	if (n < 0) return 0;
	if (n == 0) return 1;

	return countWays(n-1) + countWays(n-2) + countWays(n-3);
}

int _countWaysOpt(int n, std::vector<int> &memo) {
	if (n < 0) return 0;
	if (n == 0) return 1;
	if (memo[n] != -1)
		return memo[n];

	memo[n] = _countWaysOpt(n-1, memo) + _countWaysOpt(n-2, memo) + _countWaysOpt(n-3, memo);
	return memo[n];

}

int countWaysOpt(int n) {
	std::vector<int> memo = std::vector<int>(n + 1, -1);
	return _countWaysOpt(n, memo);
}

bool findPath(std::vector<std::vector<bool>> m, int right, int down, std::list<std::pair<int,int>> &path) {
	std::cout << "r:" << right << " d:" << down << " size:" << m.size() << std::endl;
	if (right == m.size() - 1 && down == m.size() - 1) return true;
	if( m[right][down] ) {
		if (right == m.size() - 1 && findPath(m, right, down + 1, path)) {
			path.push_back(std::pair<int,int>(right, down));
			return true;
		} else if (down == m.size() - 1 && findPath(m, right + 1, down, path)) {
			path.push_back(std::pair<int,int>(right, down));
			return true;
		} else if (findPath(m, right + 1, down, path) || findPath(m, right, down + 1, path)) {
			path.push_back(std::pair<int,int>(right, down));

			return true;

		}
	}

	return false;
}

std::list<std::pair<int,int>> findPath(std::vector<std::vector<bool>> m) {
	if (m.size() == 0) {
		return std::list<std::pair<int,int>>();
	}
	std::list<std::pair<int,int>> path = std::list<std::pair<int,int>>();
	if (!findPath(m,0,0,path))
		std::cout << "PATH NOT FOUND!" << std::endl;
	return path;
}

bool findPathOpt(std::vector<std::vector<bool>> m, std::vector<std::vector<bool>> &visited,
		int right, int down, std::list<std::pair<int,int>> &path) {
	std::cout << "r:" << right << " d:" << down << " size:" << m.size() << std::endl;
	if (right == m.size() - 1 && down == m.size() - 1) return true;
	if (visited[right][down]) {
		std::cout << "HIT" << std::endl;
		return false;
	}

	visited[right][down] = true;

	if( m[right][down] ) {
		if (right == m.size() - 1 && findPathOpt(m, visited, right, down + 1, path)) {
			path.push_back(std::pair<int,int>(right, down));
			return true;
		} else if (down == m.size() - 1 && findPathOpt(m, visited, right + 1, down, path)) {
			path.push_back(std::pair<int,int>(right, down));
			return true;
		} else if (findPathOpt(m, visited, right + 1, down, path) || findPathOpt(m, visited, right, down + 1, path)) {
			path.push_back(std::pair<int,int>(right, down));
			return true;
		}
	}
	return false;
}

std::list<std::pair<int,int>> findPathOpt(std::vector<std::vector<bool>> m) {
	if (m.size() == 0) {
		return std::list<std::pair<int,int>>();
	}
	std::vector<std::vector<bool>> visited =
			std::vector<std::vector<bool>>(m.size(), std::vector<bool>(m.size(), false));
	std::list<std::pair<int,int>> path = std::list<std::pair<int,int>>();
	if (!findPathOpt(m,visited,0,0,path))
		std::cout << "PATH NOT FOUND!" << std::endl;
	return path;
}

std::list<std::vector<int>> powerSets(std::vector<int> set) {
	std::list<int> s;
	std::list<std::vector<int>> pset;
	std::copy( set.begin(), set.end(), std::back_inserter( s ) );
	powerSets(s, pset);
	return pset;
}

void powerSets(std::list<int> set, std::list<std::vector<int>> &pset) {
	if (set.size() == 0) return;
	if (pset.empty()) pset.push_back(std::vector<int>());

	int curr = set.front();
	set.pop_front();

	pset = addToPset(pset, curr);
	std::cout << "pset size:" << pset.size() << std::endl;

	powerSets(set, pset);
}

std::list<std::vector<int>> addToPset(std::list<std::vector<int>> pset, int val) {
	std::list<std::vector<int>> ret;
	while (! pset.empty()) {
		std::vector<int> curr = pset.front();
		pset.pop_front();
		ret.push_back(curr);
		curr.push_back(val);
		ret.push_back(curr);
	}
	return ret;
}

unsigned int multiply(unsigned int a, unsigned int b) {
	if (b == 0) return 0;
	int i = 0;
	while ( 1 << i <= b ) i++;
	return (a << (i - 1)) + multiply(a, (b - (1 << (i - 1))));
}

void permute(std::vector<int> &in, std::vector<int> &out,
			 std::vector<bool> &used, std::vector<std::vector<int>> &permutations) {
	if (out.size() == in.size()) permutations.push_back(out);
	for (int i = 0; i < in.size(); i++) {
		if ( used[i] ) continue;
		out.push_back(in[i]);
		used[i] = true;
		permute(in, out, used, permutations);
		used[i] = false;
		out.pop_back();
	}
}

std::vector<std::vector<int>> permute(std::vector<int> in) {
	std::vector<bool> used = std::vector<bool>(in.size(), false);
	std::vector<int> out;
	std::vector<std::vector<int>> permutations;
	permute(in, out, used, permutations);
	return permutations;
}

BinaryNode<int>* minimalTree(std::vector<int> array, int start, int end)
{
	if (end < start) return nullptr;

	int val = (start + end) / 2;

	BinaryNode<int>* n = new BinaryNode<int>(array[val]);
	// go right
	n->right = minimalTree(array, val + 1, end);
	// go left
	n-> left = minimalTree(array, start, val - 1);

	return n;
}






