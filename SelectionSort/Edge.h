#pragma once
#include<iostream>
#include<cassert>
#include<vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

//�ߵ�Ȩֵ�����Ϳ��ܲ�ֻ��double�����԰���������Ϊģ�壬����˵�ǿ��ǵķǳ��ܵ��ˡ�

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

	// ��Щ�����������ʹ��Edge��Ϊ���е�����ʱ�����ԱȽϴ�С���������shiftUp��shiftDown
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
	int n, m;      // n�Ƕ�������m�����ӵıߵĸ�����
	bool directed; // ��������ͼ��������ͼ
	vector<vector< Edge<Weight>* >> g; // ע��ָ��using namespace std;

public:
	DenseGraph(int n, bool directed) {
		this->n = n;
		this->m = 0; // ��ʼʱ��ÿ��ͼ�ı���Ϊ0
		this->directed = directed;
		for (int i = 0; i < n; i++)
			g.push_back(vector< Edge<Weight>* >(n, NULL)); // ������n*n�ľ���
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

		// ������ظ��ߣ��ú����ı߸���֮ǰ�ıߡ�
		if (hasEdge(v, w)) {
			delete g[v][w];
			if (!directed)//���������ͼ��Ҫ��ɾһ��
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

		// �ӵ�ǰindex��ʼ���������ֱ���ҵ�һ��g[v][index]Ϊtrue
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




// ϡ��ͼ - �ڽӱ�
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
			g.push_back(vector<Edge<Weight>*>()); //��ʼ��ÿ����Ϊ�� 
										//������ṹ���˿�����Vectorʵ��,������������������ŵ�����ɾ��һ���ߺ����ף�
	}
	~SparseGraph() {
		for (int i = 0; i < n; i++)
			for (int j = 0; j < g[i].size(); j++)
				delete g[i][j];
	}
	int V() { return n; }
	int E() { return m; }
	// �ڽӱ�����Ȼ����ƽ�бߣ���ҪhasEdge���ж�һ��
	void addEdge(int v, int w, Weight weight) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		g[v].push_back(new Edge<Weight>(v, w, weight));
		if (v != w && !directed) { //�����Ի���
			g[w].push_back(new Edge<Weight>(w, v, weight));
		}
		// û�п�������ظ�push_back���µ�m���࣬��hasEdgeʱ�临�Ӷ�ΪO��n��
		// ���������ǵ�Ӧ���У�ע�ⲻҪ�ظ�addEdge�ͺ�
		m++;
	}
	// ϡ���Ͳ�����ƽ�бߵ�������
	// ���Ҫ����ƽ�бߣ����ʱʱ�临�ӶȾ���O��n)
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
		SparseGraph & G; // һ��ͼ
		int v;           // ���ͼ��ĳ������
		int index;

	public:

		// ���ڽڵ��������������
		// ��ʵ���ھ������õ����þ��Ǳ��ⲻ��Ҫ�ĸ��ƣ���Լʱ��Ϳռ�
		// ���Ӧ�þ���ĳ����������ʵ��˼·������vector<int>::iterator���ֵ�
		adjIterator(SparseGraph &graph, int v) :G(graph) {
			this->v = v;
			this->index = 0;
		}

	    Edge<Weight>* begin() {
			index = 0;// ���ǵ��û����ܶ�ε���begin,����ÿ�ε��ö��Ὣindex��Ϊ0
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

