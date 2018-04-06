#pragma once
#include<vector>
#include<cassert>
#include<iostream>
using namespace std;

// 稠密图-邻接矩阵
// 这种方式就自动将平行边合成了一个边，所以不用care平行边的问题。
class DenseGraph {

private:
	int n, m; // n是顶点数，m是连接的边的个数。
	bool directed; // 看是有向图还是无向图
	vector<vector<bool>> g; // 注意指出using namespace std;

public:
	DenseGraph(int n, bool directed) {
		this->n = n;
		this->m = 0; // 开始时令每个图的边数为0
		this->directed = directed;
		for (int i = 0; i < n; i++)
			g.push_back(vector<bool>(n, false)); // 创建了n*n的矩阵
	}
	~DenseGraph(){}
	int V() { return n; }
	int E() { return m; }
	void addEdge(int v, int w) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		if (hasEdge(v, w))
			return;
		g[v][w] = true;
		if (!directed)
			g[w][v] = true;
		m++;
	}

	bool hasEdge(int v, int w) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		return g[v][w];
	}
	void show() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				cout << g[i][j] << "  ";
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

		int begin() {
			index = -1;
			return next();
		}

		int next() {
			for (index += 1; index < G.V();index++)
				if (G.g[v][index])
					return index;
			return -1;
		}

		bool end() {
			return index >= G.V();
		}

	};

};



// 稀疏图 - 邻接表
class SparseGraph {
private:
	int n, m;
	bool directed;
	vector<vector<int>> g;
public:
	SparseGraph(int n, bool directed) {
		this->n = n;
		this->m = 0;
		this->directed = directed;
		for (int i = 0; i < n; i++)
			g.push_back(vector<int>()); //初始化每个都为空 
		                             //（这个结构除了可以用Vector实现,还可以用链表，链表的优点在于删除一条边很容易）
	}
	~SparseGraph(){}
	int V() { return n; }
	int E() { return m; }
	// 邻接表不能天然消除平行边，需要hasEdge来判断一下
	void addEdge(int v, int w) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		g[v].push_back(w);
		if (v!= w && !directed) { //考虑自环边
			g[w].push_back(v);
		}
		// 没有考虑如果重复push_back导致的m增多，因hasEdge时间复杂度为O（n）
		// 所以在我们的应用中，注意不要重复addEdge就好
		m++;
	}
	// 如果要消除平行边，最差时时间复杂度就是O（n)
	bool hasEdge(int v, int w) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		for (int i = 0; i < g[v].size(); i++)
			if (g[v][i] == w)
				return true;
		return false;
	}

	void show() {
		for (int i = 0; i < n; i++) {
			cout << "vertex" << i << ":  ";
			for (int j = 0; j < g[i].size(); j++)
				cout << g[i][j] << "  ";
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

		int begin() {
			index = 0;// 考虑到用户可能多次调用begin,所以每次调用都会将index置为0
			if (G.g[v].size())
				return G.g[v][index];
			return -1;
		}

		int next() {
			index++;
			if (index < G.g[v].size())
				return G.g[v][index];
			return -1;
		}

		bool end() {
			return index >= G.g[v].size();
		}


	};

};

//同样是遍历一遍每个顶点所连接的边，邻接矩阵的时间复杂度为O（V^2),而连接表为O（E）

// 随机生成一张图并遍历的方法(SparseGraph 替换为DenseGraph，其他不用修改，生成的就是稠密图)
/*
     int N = 20; //节点个数
	 int M = 100; //边的个数
	 srand(time(NULL));

	 SparseGraph g1(N, false);// N个节点的无向图
	 for (int i = 0; i < M ; i++){
		 int a = rand() % N;
		 int b = rand() % N;
		 g1.addEdge(a, b);
	 }

	 for (int v = 0; v < N; v++) {
		 cout << v << ":";
		 SparseGraph::adjIterator adj(g1, v);
		 for (int w = adj.begin(); !adj.end(); w = adj.next())
			 cout << w << " ";
		 cout << endl;
	 }
 */


