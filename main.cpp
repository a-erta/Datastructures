/*
 * main.cpp
 *
 *  Created on: Dec 19, 2015
 *      Author: alessandroerta
 */

#include "tree.h"
#include "sorting.h"
#include "recursion.h"
#include "utils.h"
#include <chrono>

int main() {
	auto print = [](int y) { std::cout << y << std::endl; };
	// std::vector<int> array = std::vector<int>({5,7,8,3,1,6,2,12,9,4,11,10});

	std::vector<int> array;

	for (int i = 0; i < 5; i++) {
		array.push_back(rand() % 5);
	}

	std::cout << "Original:" << std::endl;

	Sorting<int>::quicksort(array, new IntComparator());
	//Sorting<int>::selectionSort(array, new IntComparator());
	//Sorting<int>::mergesort(array, new IntComparator());
	//std::sort(array.begin(), array.end());

	std::cout << "Sorted:" << std::endl;

	//printVector(array);
	int n = -345576;
	std::cout << "num Ones in " << n << " => " << numOnes(n) << std::endl;

	std::cout << "This machine is " << (isLittleEndian() == 1 ? "little endian" : "big endian") << std::endl;

	{
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		std::cout << "with 20 steps the ways are: " << countWays(20) << " ";
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
		std::cout << "with slow countWays exec time: " << duration << std::endl;
	}

	{
		std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
		std::cout << "with 20 steps the ways are: " << countWaysOpt(20) << " ";
		std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
		std::cout << "with slow countWaysOpt exec time: " << duration << std::endl;
	}

	// maze path

	std::vector<std::vector<bool> > maze = std::vector<std::vector<bool> >(3, std::vector<bool>(3, true));
	maze[0][1] = false;
	maze[2][0] = false;
	maze[2][1] = false;

{ // slow robot in grid test
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::list<std::pair<int,int> > path = findPath(maze);

	while (path.begin() != path.end()) {
		std::pair<int,int> val = path.back();
		std::cout << "(" << val.first << "," << val.second << ")";
		path.pop_back();
	}
	std::cout << std::endl;
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	std::cout << "findPath(maze) exec time: " << duration << std::endl;
}

{ // fast robot in grid test
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::list<std::pair<int,int> > path = findPathOpt(maze);

	while (path.begin() != path.end()) {
		std::pair<int,int> val = path.back();
		std::cout << "(" << val.first << "," << val.second << ")";
		path.pop_back();
	}
	std::cout << std::endl;
	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
	std::cout << "findPathOpt(maze) exec time: " << duration << std::endl;
}

{ // Power set test
	printVector(array);
	std::list<std::vector<int> > pset = powerSets(array);
	/*while (!pset.empty()) {
		std::vector<int> curr = pset.front();
		pset.pop_front();
		printVector(curr);
	}*/
}

{
	unsigned int a = 232;
	unsigned int b = 128;
	unsigned int val = multiply(a, b);
	std::cout << a << " * " << b << " = " << val << std::endl;
}

{
	std::cout << "Priority Queue" << std::endl;
	PriorityQueue<int> prio = PriorityQueue<int>(new IntComparator());
	prio.push(60);
	prio.push(30);
	prio.push(11);
	prio.print();
	prio.update(11, 32);
	prio.print();

	PriorityQueue<int> prio2 = PriorityQueue<int>(new IntComparator(IntComparator::ORDER::DESC));
	prio2.push(60);
	prio2.push(30);
	prio2.push(11);
	prio2.print();
	std::cout << "front:" << prio2.top() << std::endl;
	prio2.pop();
	prio2.print();
}

{
	// build the graph with 4 nodes
	GraphNode<int> *one = new GraphNode<int>(1);
	GraphNode<int> *two = new GraphNode<int>(2);
	GraphNode<int> *three = new GraphNode<int>(3);
	GraphNode<int> *four = new GraphNode<int>(4);
	GraphNode<int> *five = new GraphNode<int>(5);
	GraphNode<int> *six = new GraphNode<int>(6);
	GraphNode<int> *seven = new GraphNode<int>(7);

	one->addNeighbor(two, 3);
	one->addNeighbor(three, 5);

	two->addNeighbor(four, 6);
	two->addNeighbor(seven, 3);

	three->addNeighbor(four, 1);

	four->addNeighbor(five, 3);
	four->addNeighbor(six, 7);

	five->addNeighbor(seven, 1);

	Graph<int> graph = Graph<int>();
	graph.addNode(one);
	graph.addNode(two);
	graph.addNode(three);
	graph.addNode(four);
	graph.addNode(five);
	graph.addNode(six);
	graph.addNode(seven);

	std::cout << "graph ready" << std::endl;

	std::list<GraphNode<int>*> path = graph.dijkstra(one, seven);


}

{
	BinarySearchTree<int>* tree = new BinarySearchTree<int>();

	tree->root = minimalTree(array, 0, array.size() - 1);


	std::cout << "----INORDER--------" << std::endl;
	tree->inOrderVisit(print);
	std::cout << "----PREORDER--------" << std::endl;
	tree->preOrderVisit(print);
	std::cout << "----POSTORDER--------" << std::endl;
	tree->postOrderVisit(print);

	std::cout << "depth:" << tree->treeDepth() << std::endl;

	std::vector<std::vector<BinaryNode<int>*> > levels = tree->getLevels();
	std::vector<std::vector<std::vector<int> > > sequences;

	for (int i = 0; i < levels.size(); i ++) {
		sequences.push_back(permute(buildIntArray(levels[i])));
	}

	for (int i = 0; i < sequences.size(); i++) {
		for (int j = 0; j < sequences[i].size(); j++) {
			for (int k = 0; k < sequences[i][j].size(); k++ )
				std::cout << sequences[i][j][k] << ",";
			std::cout << std::endl;
		}
	}
}

{ // longest sequence of ones
	int longest = longestSequence(8190);
	std::cout << "longest: " << longest << std::endl;
}

	return 0;
}


