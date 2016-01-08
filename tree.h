/*
 * tree.h
 *
 *  Created on: Dec 19, 2015
 *      Author: alessandroerta
 */

#ifndef TREE_H_
#define TREE_H_

#include <cstddef>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <queue>
#include <climits>
#include "sorting.h"

template<class T>
class PriorityQueue {
	std::vector<T> queue;
	Comparator<T> *comp;
	int binarySearchArray(T val);
	int binarySearchArray(T val, int start, int end);
public:
	PriorityQueue() : comp(new IntComparator()) {}
	PriorityQueue(Comparator<T> *comp = new IntComparator());
	~PriorityQueue() { if (comp != nullptr) delete comp; }
	void push(T val);
	T top();
	void pop();
	T find(T val);
	bool update(T val, T new_val);
	void print();
	bool empty() { return this->queue.empty(); }

};

template<class T>
class GraphNode {
	T data;
	std::map<GraphNode<T>*, int> neighbors;
public:
	GraphNode() : data(T()) {};
	GraphNode(T val) { data = val; };
	void addNeighbor(GraphNode<T>* val, int weight);
	T getData() { return data; }
	std::map<GraphNode<T>*, int> getNeighbors() { return neighbors; }
};

template<class T>
using ListNode = std::list<GraphNode<T>*> ;
template<class T>
using MapGraphNodeInt = std::map<GraphNode<T>*, int> ;

template<class T>
class GraphNodeIntPairComparator : public Comparator<std::pair<GraphNode<T>*, int> > {
public:
	GraphNodeIntPairComparator() {}
	bool compare(std::pair<GraphNode<T>*, int> a, std::pair<GraphNode<T>*, int> b) {
		return a.second > b.second;
	}
	~GraphNodeIntPairComparator(){}
};

template<class T>
class Graph {
	ListNode<T> nodes;

public:
	Graph() {};
	void addNode(GraphNode<T>* val);
	ListNode<T> dijkstra(GraphNode<T> *src, GraphNode<T> *dst);
};

template<class T>
class BinaryNode {
public:
	T data;
	BinaryNode *parent;
	BinaryNode *left;
	BinaryNode *right;
	BinaryNode() : parent(nullptr), left(nullptr), right(nullptr) {};
	BinaryNode(T d) : data(d), parent(nullptr), left(nullptr), right(nullptr) {};
};

template<class T>
class BinaryTree {
	void deleteTree(BinaryNode<T>* root);
	void inOrderVisit(BinaryNode<T> *r, std::function<void (T)> f);
	void preOrderVisit(BinaryNode<T> *r, std::function<void (T)> f);
	void postOrderVisit(BinaryNode<T> *r, std::function<void (T)> f);
public:
	BinaryNode<T> *root;
	BinaryTree() : root(nullptr) {};
	~BinaryTree();
	bool addLeft(T val, BinaryNode<T>* parent);
	bool addRight(T val, BinaryNode<T>* parent);
	void inOrderVisit(std::function<void (T)> f) { inOrderVisit(root, f); };
	void preOrderVisit(std::function<void (T)> f) { preOrderVisit(root, f); };
	void postOrderVisit(std::function<void (T)> f) { postOrderVisit(root, f); };
	int treeDepth(BinaryNode<T> *r);
	int treeDepth();

};

template<class T>
class BinarySearchTree : public BinaryTree<T> {
	bool recursiveAddNode(T val, BinaryNode<T>* &root);
public:
	bool addNode(T val);
	bool recursiveAddNode(T val);
	std::vector<BinaryNode<T>*> getLevel(std::vector<BinaryNode<T>*>);
	std::vector<std::vector<BinaryNode<T>*> > getLevels();
};

template <class T>
BinaryTree<T>::~BinaryTree() {
	deleteTree(root);
}

template <class T>
void BinaryTree<T>::deleteTree(BinaryNode<T>* root) {
	if (root == nullptr) return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

template <class T>
bool BinaryTree<T>::addLeft(T val, BinaryNode<T>* parent) {
	if(parent == nullptr) return false;
	if(parent->left == nullptr) {
		parent->left = new BinaryNode<T>(val);
		return true;
	}
	return false;
}

template <class T>
bool BinaryTree<T>::addRight(T val, BinaryNode<T>* parent) {
	if(parent == nullptr) return false;
	if(parent->right == nullptr) {
		parent->right = new BinaryNode<T>(val);
		return true;
	}
	return false;
}

template <class T>
void BinaryTree<T>::inOrderVisit(BinaryNode<T> *r, std::function<void (T)> f) {
	if (r == nullptr) return;
	inOrderVisit(r->left, f);
	f(r->data);
	inOrderVisit(r->right, f);
}

template <class T>
void BinaryTree<T>::preOrderVisit(BinaryNode<T> *r, std::function<void (T)> f) {
	if (r == nullptr) return;
	f(r->data);
	preOrderVisit(r->left, f);
	preOrderVisit(r->right, f);
}

template <class T>
void BinaryTree<T>::postOrderVisit(BinaryNode<T> *r, std::function<void (T)> f) {
	if (r == nullptr) return;
	postOrderVisit(r->left, f);
	postOrderVisit(r->right, f);
	f(r->data);
}

template <class T>
int BinaryTree<T>::treeDepth(BinaryNode<T> *r) {
	if (r == nullptr ) return 0;
	return 1 + std::max(treeDepth(r->left), treeDepth(r->right));
}

template <class T>
int BinaryTree<T>::treeDepth() {
	return treeDepth(root);
}

template <class T>
bool BinarySearchTree<T>::addNode(T val) {
	BinaryNode<T>* curr = this->root;
	while ( curr != nullptr ) {
		if (val > curr->data) {
			if (curr->right == nullptr) {
				this->addRight(val, curr);
				return true;
			} else curr = curr->right;
		} else {
			if (curr->left == nullptr) {
				this->addLeft(val, curr);
				return true;
			} else curr = curr->left;
		}
	}
	this->root = new BinaryNode<T>(val);
	return true;
}

template <class T>
bool BinarySearchTree<T>::recursiveAddNode(T val) {
	return recursiveAddNode(val, this->root);
}

template <class T>
bool BinarySearchTree<T>::recursiveAddNode(T val, BinaryNode<T>* &r) {
	if (r == nullptr ) {
		r = new BinaryNode<T>(val);
		return true;
	}
	if (val > r->data) {
		if (r->right == nullptr) {
			this->addRight(val, r);
			return true;
		} else recursiveAddNode(val, r->right);
	} else {
		if (r->left == nullptr) {
			this->addLeft(val, r);
			return true;
		} else recursiveAddNode(val, r->left);
	}
	return false;
}

template <class T>
std::vector<BinaryNode<T>*> BinarySearchTree<T>::getLevel(std::vector<BinaryNode<T>*> in) {
	std::vector<BinaryNode<T>*> ret = std::vector<BinaryNode<T>*>();
	for (int i = 0; i < in.size(); i++) {
		if(in[i]->left != nullptr)
			ret.push_back(in[i]->left);
		if(in[i]->right != nullptr)
			ret.push_back(in[i]->right);
	}
	return ret;
}

template <class T>
std::vector<std::vector<BinaryNode<T>*> > BinarySearchTree<T>::getLevels() {
	std::vector<std::vector<BinaryNode<T>*> > ret = std::vector<std::vector<BinaryNode<T>*> >();
	if(this->root != nullptr)
		ret.push_back(std::vector<BinaryNode<T>*>({this->root}));
	int i = 0;
	std::vector<BinaryNode<T>*> tmp = this->getLevel(ret[i++]);
	while (tmp.size() > 0) {
		ret.push_back(tmp);
		tmp = this->getLevel(ret[i++]);
	}
	return ret;
}

template <class T>
void GraphNode<T>::addNeighbor(GraphNode<T>* val, int weight) {
	this->neighbors[val] = weight;
}

template <class T>
void Graph<T>::addNode(GraphNode<T>* val) {
	this->nodes.push_back(val);
}

template <class T>
std::list<GraphNode<T>*> Graph<T>::dijkstra(GraphNode<T>* src, GraphNode<T>* dst) {
	// initialize
	MapGraphNodeInt<T> dist;
	for (typename ListNode<T>::const_iterator iterator = this->nodes.begin(),
			end = this->nodes.end(); iterator != end; ++iterator) {
	    dist[*iterator] = INT_MAX;
	}
	PriorityQueue<std::pair<GraphNode<T>*, int> > prio(new GraphNodeIntPairComparator<T>());
	prio.push(std::pair<GraphNode<T>*, int>(src, 0));
	dist[src] = 0;
	std::map<GraphNode<T>*, GraphNode<T>*> pred = std::map<GraphNode<T>*, GraphNode<T>*>();

	// run the algorithm
	while (!prio.empty()) {
		std::pair<GraphNode<T>*, int> curr = prio.top();
		prio.pop();
		if (curr.first == dst) break;

		MapGraphNodeInt<T> neighbors = curr.first->getNeighbors();
		for (typename MapGraphNodeInt<T>::const_iterator i = neighbors.begin();
				i != neighbors.end(); ++i) {
			GraphNode<T> *currNeigh = i->first;
			int new_dist = dist[curr.first] + i->second;
			if (new_dist < dist[i->first]) {
				if (dist[i->first] == INT_MAX) {
					prio.push(std::pair<GraphNode<T>*, int>(currNeigh, new_dist));
				} else {
					prio.update(std::pair<GraphNode<T>*, int>(currNeigh, dist[i->first]),
								std::pair<GraphNode<T>*, int>(currNeigh, new_dist));
				}
				dist[i->first] = new_dist;
				pred[currNeigh] = curr.first; // update the predecessor
			}
		}
	}

	std::cout << "node:dist from src: node " << src->getData() << std::endl;
	for (typename MapGraphNodeInt<T>::const_iterator i = dist.begin();
					i != dist.end(); ++i) {
		printf("%d:%d ", i->first->getData(), i->second);
	}
	std::cout << std::endl;

	std::cout << "MST from src node " << src->getData() << " to dst node " << dst->getData() << std::endl;
	std::list<GraphNode<T>*> path;
	GraphNode<T>* end = dst;
	path.push_back(end);
	printf("%u->", end->getData());
	while (pred[end] != src) {
		printf("%u->", pred[end]->getData());
		path.push_back(pred[end]);
		end = pred[end];
	}
	path.push_back(src);
	printf("%u\n", src->getData());

	return path;
}

template <class T>
PriorityQueue<T>::PriorityQueue(Comparator<T> *c) {
	this->comp = c;
}

template <class T>
void PriorityQueue<T>::push(T val) {
	this->queue.push_back(val);
	Sorting<T>::quicksort(this->queue, this->comp);
}

template <class T>
T PriorityQueue<T>::top() {
	return this->queue.front();
}

template <class T>
void PriorityQueue<T>::pop() {
	if (this->queue.empty()) return;
	this->queue.erase(this->queue.begin());
}

template <class T>
T PriorityQueue<T>::find(T val) {
	return binarySearchArray(val);
}

template <class T>
int PriorityQueue<T>::binarySearchArray(T val) {
	if (this->queue.empty()) return -1;
	return binarySearchArray(val, 0, this->queue.size() - 1);
}

template <class T>
int PriorityQueue<T>::binarySearchArray(T val, int start, int end) {
	if (start > end) return -1;
	int mid = (start + end) / 2;
	if (val == this->queue[mid]) return mid;
	if (this->comp->compare(val, this->queue[mid])) // right
		return binarySearchArray(val, mid + 1, end);
	else return binarySearchArray(val, 0, mid - 1); // left
}


template <class T>
void PriorityQueue<T>::print() {
	for (int i = 0; i < this->queue.size(); i++)
		std::cout << this->queue[i] << " ";
	std::cout << std::endl;
}

template <class T>
bool PriorityQueue<T>::update(T val, T new_val) {
	int idx = binarySearchArray(val);
	if (idx != -1) {
		this->queue[idx] = new_val;
		Sorting<T>::quicksort(this->queue, this->comp);
		return true;
	}
	return false;
}



#endif /* TREE_H_ */
