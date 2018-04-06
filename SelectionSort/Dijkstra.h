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
	int s; // ��Դ���·����Դ����

	Weight * distTo;       // �����㵽ԭ�����̾�������� 
	bool * marked;          // �Ѿ��ҵ����·���Ķ���
	vector<Edge<Weight>*> from ; // ·����ÿ���������һ�����㡣

public:
	Dijkstra(Graph &graph, int s) :G(graph) {

		this->s = s;
		distTo = new Weight[G.V()];
		marked = new bool[G.V()];
		for (int i = 0; i < G.V(); i++) {
			distTo[i] = Weight();//�����double,int,��...��ʵҲ�й��캯���������ʼ��Ϊ0
			marked[i] = false;
			from.push_back(NULL);
		}

		IndexMinHeap<Weight> ipq(G.V());

		// Dijkstra
		distTo[s] = Weight(); // ����ʼ��Ϊ0
		from[s] = new Edge<Weight>(s, s, 0); // ��Ƶ��û����һ��
		marked[s] = true;
		ipq.insert(s, distTo[s]);
		while (!ipq.isEmpty()) {

			int v = ipq.extractMinIndex();
			
			// distTo[v]����s��v����̾���
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

	void shortestPath(int w, vector<Edge<Weight>> & vec)  // ·�������vec��
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