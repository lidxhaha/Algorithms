#pragma warning(disable:4996)  
#include<iostream>
//#include "SortTestHelper.h"
//#include "Sort.h"
//#include "Heap.h"
//#include "Graph.h"
//#include "ReadGraph.h"
//#include "Component.h"
#include "Edge.h"
//#include "Prim.h"
//#include "Kruskal.h"
#include "Dijkstra.h"
#include "BellmanFord.h"
using namespace std;





int main()
{
	
	string filename = "testG2.txt";
	int V = 5;
	SparseGraph<int> g = SparseGraph<int>(V, true);
	ReadGraph<SparseGraph<int>, int> readGraph(g, filename);

	cout << "Test Bellman-Ford:" << endl << endl;
	BellmanFord<SparseGraph<int>, int> bellmanFord(g, 0);

	if (bellmanFord.negativeCycle())
		cout << "The graph contain negative cycle!" << endl;
	else
		for (int i = 1; i  < V; i++) {
			cout << "Shortest Path to " << i << " : " << bellmanFord.shortestPathTo(i) << endl;
			bellmanFord.showPath(i);
			cout << "-------------" << endl;
		}
	



	
	
	getchar();
	return 0;
}