#pragma once
#include<vector>
#include<cassert>
#include<iostream>
using namespace std;

// ����ͼ-�ڽӾ���
// ���ַ�ʽ���Զ���ƽ�бߺϳ���һ���ߣ����Բ���careƽ�бߵ����⡣
class DenseGraph {

private:
	int n, m; // n�Ƕ�������m�����ӵıߵĸ�����
	bool directed; // ��������ͼ��������ͼ
	vector<vector<bool>> g; // ע��ָ��using namespace std;

public:
	DenseGraph(int n, bool directed) {
		this->n = n;
		this->m = 0; // ��ʼʱ��ÿ��ͼ�ı���Ϊ0
		this->directed = directed;
		for (int i = 0; i < n; i++)
			g.push_back(vector<bool>(n, false)); // ������n*n�ľ���
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



// ϡ��ͼ - �ڽӱ�
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
			g.push_back(vector<int>()); //��ʼ��ÿ����Ϊ�� 
		                             //������ṹ���˿�����Vectorʵ��,������������������ŵ�����ɾ��һ���ߺ����ף�
	}
	~SparseGraph(){}
	int V() { return n; }
	int E() { return m; }
	// �ڽӱ�����Ȼ����ƽ�бߣ���ҪhasEdge���ж�һ��
	void addEdge(int v, int w) {
		assert(v >= 0 && v < n);
		assert(w >= 0 && w < n);
		g[v].push_back(w);
		if (v!= w && !directed) { //�����Ի���
			g[w].push_back(v);
		}
		// û�п�������ظ�push_back���µ�m���࣬��hasEdgeʱ�临�Ӷ�ΪO��n��
		// ���������ǵ�Ӧ���У�ע�ⲻҪ�ظ�addEdge�ͺ�
		m++;
	}
	// ���Ҫ����ƽ�бߣ����ʱʱ�临�ӶȾ���O��n)
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

		int begin() {
			index = 0;// ���ǵ��û����ܶ�ε���begin,����ÿ�ε��ö��Ὣindex��Ϊ0
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

//ͬ���Ǳ���һ��ÿ�����������ӵıߣ��ڽӾ����ʱ�临�Ӷ�ΪO��V^2),�����ӱ�ΪO��E��

// �������һ��ͼ�������ķ���(SparseGraph �滻ΪDenseGraph�����������޸ģ����ɵľ��ǳ���ͼ)
/*
     int N = 20; //�ڵ����
	 int M = 100; //�ߵĸ���
	 srand(time(NULL));

	 SparseGraph g1(N, false);// N���ڵ������ͼ
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


