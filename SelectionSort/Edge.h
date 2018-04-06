#pragma once
#include<iostream>
#include<cassert>
#include<vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//边的权值的类型可能不只有double，所以把其类型设为模板，可以说是考虑的非常周到了。

template<typename Weight>
class Edge {
private:
	int a, b;
	Weight weight;
public:
	Edge(int a, int b, Weight weight) {
		this->a = a;
		this->b = b;
		this->weight = weight;
	}

	Edge() {};
	~Edge() {};
	int v() { return a; }
	int w() { return b; }
	Weight wt() { return weight; }
	int other(int x) {
		assert(x == a || x == b);
		return x == a ? b : a;
	}
	friend ostream& operator<<(ostream &os, const Edge &e) {
		os << e.a << "-" << e.b << ": " << e.weight;
		return os;
	}

	// 这些运算符的重载使得Edge作为堆中的数据时，可以比较大小，今而可以shiftUp和shiftDown
	bool operator<(Edge<Weight>& e) {
		return weight < e.wt();
	}

	bool operator<=(Edge<Weight>& e) {
		return weight <= e.wt();
	}

	bool operator>(Edge<Weight>& e) {
		return weight > e.wt();
	}

	bool operator>=(Edge<Weight>& e) {
		return weight >= e.wt();
	}

	bool operator==(Edge<Weight>& e) {
		return weight == e.wt();
	}

};


template<typename Weight>
class DenseGraph {
private:
	int n, m;      // n是顶点数，m是连接的边的个数。
	bool directed; // 看是有向图还是无向图
	vector<vector< Edge<Weight>* >> g; // 注意指出using namespace std;

public:
	DenseGraph(int n, bool directed) {
		this->n = n;
		this->m = 0; // 开始时令每个图的边数为0
		this->directed = directed;
		for (int i = 0; i < n; i++)
			g.push_back(vector< Edge<Weight>* >(n, NULL)); // 创建了n*n的矩阵
	}
	~DenseGraph() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n;j++)
				if (g[i][j] != NULL)
					delete g[i][j];
	}
	int V() { return n; }
	int E() { return m; }

	void addEdge(int v, int w, Weight weight) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);

		// 如果有重复边，让后来的边覆盖之前的边。
		if (hasEdge(v, w)) {
			delete g[v][w];
			if (!directed)//如果是无向图还要多删一个
				delete g[w][v];
			m--;
		}
		
		g[v][w] = new Edge<Weight>(v, w, weight);
		if (!directed)
			g[w][v] = new Edge<Weight>(w,v,weight);
		m++;
	}

	bool hasEdge(int v, int w) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		return g[v][w]!=NULL;
	}
	void show() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				if (g[i][j])
					cout << g[i][j]->wt() << "  ";
				else
					cout << "NULL    ";
			cout << endl;
		}


	}
	class adjIterator {
	private:
		DenseGraph & G;
		int v;
		int index;
	public:

		adjIterator(DenseGraph & graph, int v) :G(graph) {
			this->v = v;
			this->index = -1;
		}

	    Edge<Weight>* begin() {
			index = -1;
			return next();
		}

		// 从当前index开始向后搜索，直到找到一个g[v][index]为true
		Edge<Weight>* next() {
			for (index += 1; index < G.V();index++)
				if (G.g[v][index])
					return G.g[v][index];
			return NULL;
		}

		bool end() {
			return index >= G.V();
		}

	};

};



template<typename Graph, typename Weight>
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
			Weight w;
			ss >> a >> b >> w;
			assert(a >= 0 && a < V);
			assert(b >= 0 && b < V);
			graph.addEdge(a, b, w);
		}
	}
};




// 稀疏图 - 邻接表
template<typename Weight>
class SparseGraph {
private:
	int n, m;
	bool directed;
	vector<vector<Edge<Weight>*>> g;
public:
	SparseGraph(int n, bool directed) {
		this->n = n;
		this->m = 0;
		this->directed = directed;
		for (int i = 0; i < n; i++)
			g.push_back(vector<Edge<Weight>*>()); //初始化每个都为空 
										//（这个结构除了可以用Vector实现,还可以用链表，链表的优点在于删除一条边很容易）
	}
	~SparseGraph() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < g[i].size(); j++)
				delete g[i][j];
	}
	int V() { return n; }
	int E() { return m; }
	// 邻接表不能天然消除平行边，需要hasEdge来判断一下
	void addEdge(int v, int w, Weight weight) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		g[v].push_back(new Edge<Weight>(v, w, weight));
		if (v != w && !directed) { //考虑自环边
			g[w].push_back(new Edge<Weight>(w, v, weight));
		}
		// 没有考虑如果重复push_back导致的m增多，因hasEdge时间复杂度为O（n）
		// 所以在我们的应用中，注意不要重复addEdge就好
		m++;
	}
	// 稀疏表就不处理平行边的问题了
	// 如果要消除平行边，最差时时间复杂度就是O（n)
	bool hasEdge(int v, int w) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		for (int i = 0; i < g[v].size(); i++)
			if (g[v][i]->other(v) == w )
				return true;
		return false;
	}

	void show() {
		for (int i = 0; i < n; i++) {
			cout << "vertex" << i << ":  ";
			for (int j = 0; j < g[i].size(); j++)
				cout << "( to:" << g[i][j]->w() << ",wt:" << g[i][j]->wt() << ")   ";
			cout << endl;
		}
	}

	class adjIterator {

	private:
		SparseGraph & G; // 一个图
		int v;           // 这个图的某个顶点
		int index;

	public:

		// 相邻节点迭代器，很优雅
		// 其实现在觉得引用的作用就是避免不必要的复制，节约时间和空间
		// 这个应该就是某个迭代器的实现思路，比如vector<int>::iterator这种的
		adjIterator(SparseGraph &graph, int v) :G(graph) {
			this->v = v;
			this->index = 0;
		}

	    Edge<Weight>* begin() {
			index = 0;// 考虑到用户可能多次调用begin,所以每次调用都会将index置为0
			if (G.g[v].size())
				return G.g[v][index];
			return NULL;
		}

		Edge<Weight>* next() {
			index++;
			if (index < G.g[v].size())
				return G.g[v][index];
			return NULL;
		}

		bool end() {
			return index >= G.g[v].size();
		}


	};

};

