#pragma once
#include<iostream>
#include<cassert>
#include<stack>
#include<queue>
using namespace std;


//要注意这里的图不一定是一个联通的图，这里有联通分量的概念
// 这个类的主要作用是进行深度优先来访问一个图，并找出有几个联通分量。
// 还有可以判断某两个节点是否相连
template<typename Graph>
class Component {
private:
	Graph & G;
	bool *visited;
	int ccount;
	int *id;
	void dfs(int v) {
	//	if (visited[v])
		//	return;
		visited[v] = true;
		id[v] = ccount;
		typename Graph::adjIterator adj(G,v);  //指出adjIterator是一个类型而不是一个变量
		for (int i = adj.begin(); !adj.end(); i = adj.next()) {
			if (!visited[i])
		    	dfs(i);
		}
	}
public:
	Component(Graph& graph):G(graph) {
		visited = new bool[G.V()];
		id = new int[G.V()];
		ccount = 0;
		for (int i = 0; i < G.V(); i++) {
			visited[i] = false;
			id[i] = -1;
		}
			
		for (int i = 0; i < G.V(); i++)
			if (!visited[i]) {
				dfs(i);
				ccount++;
			}
	}
	~Component() {
		delete[] visited;
		delete[] id;
	}

	int count() {
		return ccount;
	}

	bool isConnected(int v, int w) {
		assert(v >= 0 && v < G.V());
		assert(w >= 0 && w < G.V());
		return id[v] == id[w];
	}

};

// 图的深度优先遍历(广度优先遍历，也是一样的)，其复杂度：
// 稀疏图（邻接表）：O(V+E)  一般V 比E 小很多
// 稠密图（邻接矩阵）：O(V^2)

// 利用深度优先找到一条路径
template<typename Graph>
class Path {
private:
	Graph & G;
	int s;
	bool* visited;
	int * from;

	void dfs(int v) {
		visited[v] = true;
		typename Graph::adjIterator adj(G, v);
		for (int i = adj.begin(); !adj.end(); i = adj.next()) {

			if (!visited[i]) {
				from[i] = v;
				dfs(i);				
			}
			
		}
	}
public:
	Path(Graph &graph, int s) :G(graph) {

		// 算法初始化
		assert(s >= 0 && s < G.V());
		visited = new bool[G.V()];
		from = new int[G.V()];
		for (int i = 0; i < G.V(); i++) {
			visited[i] = false;
			from[i] = -1;
		}
		this->s = s;
		// 寻路算法
		dfs(s);
	}

	~Path() {
		delete[] visited;
		delete[] from;
	}

	bool hasPath(int w) {
		assert(w >= 0 && w < G.V());
		return visited[w];
	}

	void path(int w, vector<int>& vec) {
		stack<int> s;

		int p = w;
		while (p != -1) {
			s.push(p);
			p = from[p];
		}
		
		vec.clear();
		while (!s.empty()) {
			vec.push_back(s.top());
			s.pop();
		}
	}

	void showPath(int w) {
		
		vector<int> vec;
		path(w, vec);
		for(int i = 0; i < vec.size(); i++) {
			cout << vec[i];
			if (i == vec.size() - 1)
				cout << endl;
			else
				cout << " -> ";
		}
	}

};

//利用广度优先求最短路径
template<typename Graph>
class ShortestPath {

private:
	Graph & G;
	int s;
	bool* visited;
	int* from;
	int* ord;
public:
	ShortestPath(Graph& graph, int s) :G(graph) {

		assert(s >= 0 && s < graph.V());

		visited = new bool[graph.V()];
		from = new int[graph.V()];
		ord = new int[graph.V()];
		for (int i = 0; i < graph.V(); i++) {
			visited[i] = false;
			from[i] = -1;
			ord[i] = -1;
		}
		this->s = s;
		queue<int> q;

		// 无向图最短路径算法
		q.push(s);
		visited[s] = true;
		ord[s] = 0;
		while (!q.empty()) {

			int v = q.front();
			q.pop();
			typename Graph::adjIterator adj(G, v);
			for (int i = adj.begin(); !adj.end(); i = adj.next()) {
				if (!visited[i]) {
					q.push(i);
					visited[i] = true;
					from[i] = v;
					ord[i] = ord[v] + 1;
				}
			}
		}


	}
	~ShortestPath() {
		delete[] visited;
		delete[] from;
		delete[] ord;
	}

	bool hasPath(int w) {
		assert(w >= 0 && w < G.V());
		return visited[w];
	}

	void path(int w, vector<int>& vec) {
		assert(w >= 0 && w < G.V());

		stack<int> s;
		int p = w;
		while (p != -1) {
			s.push(p);
			p = from[p];
		}
		vec.clear();
		while (!s.empty()) {
			vec.push_back(s.top());
			s.pop();
		}

	}

	void showPath(int w) {
		assert(w >= 0 && w < G.V());
		vector<int> vec;
		path(w, vec);
		for (int i = 0; i < vec.size(); i++) {
			cout << vec[i];
			if (i == vec.size() - 1)
				cout << endl;
			else
				cout << "->";
		}
	}
	int length(int w) {
		assert(w >= 0 && w < G.V());
		return ord[w];
	}
};