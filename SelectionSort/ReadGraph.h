#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

// ����ͬʱ������ϡ��ͼ�ͳ���ͼ��
template<typename Graph>
class ReadGraph {
public:
	ReadGraph(Graph &graph, const string &filename) {
		ifstream file(filename);
		string line;
		int V, E;
		assert(file.is_open());
		assert(getline(file, line));
		stringstream  ss(line);
		ss >> V >> E;
		assert(V == graph.V());
		for (int i = 0; i < E; i++) {
			assert(getline(file, line));
			stringstream ss(line);

			int a, b;
			ss >> a >> b;
			assert(a >= 0 && a < V);
			assert(b >= 0 && b < V);
			graph.addEdge(a, b);
		}
	}
};

/*
	string filename = "testG1.txt";
	SparseGraph g1(13, false);
	ReadGraph<SparseGraph> readGraph1(g1, filename);
	g1.show();
	cout << endl;
	DenseGraph g2(13, false);
	ReadGraph<DenseGraph> readGraph2(g2, filename);
	g2.show();
*/