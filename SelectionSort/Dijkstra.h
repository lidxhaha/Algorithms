#pragma once

#include<iostream>
#include<vector>
#include<stack>
#include "Edge.h"
#include "IndexMinHeap.h"
using namespace std;

template<typename Graph, typename Weight>
class Dijkstra {
private:
	Graph & G;
	int s; // 单源最短路径的源顶点

	Weight * distTo;       // 各个点到原点的最短距离的数组 
	bool * marked;          // 已经找到最短路径的顶点
	vector<Edge<Weight>*> from ; // 路径中每个顶点的上一个顶点。

public:
	Dijkstra(Graph &graph, int s) :G(graph) {

		this->s = s;
		distTo = new Weight[G.V()];
		marked = new bool[G.V()];
		for (int i = 0; i < G.V(); i++) {
			distTo[i] = Weight();//如果是double,int,嗯...其实也有构造函数，将其初始化为0
			marked[i] = false;
			from.push_back(NULL);
		}

		IndexMinHeap<Weight> ipq(G.V());

		// Dijkstra
		distTo[s] = Weight(); // 即初始化为0
		from[s] = new Edge<Weight>(s, s, 0); // 视频中没有这一行
		marked[s] = true;
		ipq.insert(s, distTo[s]);
		while (!ipq.isEmpty()) {

			int v = ipq.extractMinIndex();
			
			// distTo[v]就是s到v的最短距离
			marked[v] = true;

			 // Relaxation
			typename Graph::adjIterator adj(G, v);
			for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next()) {
				int w = e->other(v);
				if (!marked[w]) {
					if (from[w] == NULL || distTo[v] + e->wt() < distTo[w]) {
						distTo[w] = distTo[v] + e->wt();
						from[w] = e;
						if (ipq.contain(w))
							ipq.change(w, distTo[w]);
						else
							ipq.insert(w, distTo[w]);
					}
				}
			}
		}	
	}

	~Dijkstra() {
		delete[] distTo;
		delete[] marked;
	}

	Weight shortestPathTo(int w) {
		return distTo[w];
	}

	bool hasPathTo(int w) {
		return marked[w];
	}

	void shortestPath(int w, vector<Edge<Weight>> & vec)  // 路径输出到vec中
	{
		stack<Edge<Weight>*> s;
		Edge<Weight> *e = from[w];
		while (e->v() != e->w()) {
			s.push(e);
			e = from[e->v()];
		}
		while (!s.empty()) {
			e = s.top();
			vec.push_back(*e);
			s.pop();
		}
	}

	void showPath(int w) {
		assert(w >= 0 && w < G.V());
		assert(hasPathTo(w));
		vector<Edge<Weight>> vec;
		shortestPath(w, vec);
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i].v() << "->";
			if (i == vec.size() - 1)
				cout << vec[i].w() << endl;
		}
	}

};