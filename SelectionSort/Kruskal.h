#pragma once
#include<cassert>
#include "MinHeap.h"
#include<vector>
class UnionFind {

private:
	int* parent;
	int* rank;   // rank[i]��ʾ��iΪ���ļ��������������ȣ����Ĳ�����
	int  count;

public:
	UnionFind(int count) {
		parent = new int[count];
		rank = new int[count];
		this->count = count;
		for (int i = 0; i < count; i++) {
			parent[i] = i;
			rank[i] = 1;
		}

	}

	~UnionFind() {
		delete[] parent;
		delete[] rank;
	}

	// ���ؽڵ�p�ĸ�
	int find(int p) {
		assert(p >= 0 && p < count);

		if (p != parent[p])
			parent[p] = find(parent[p]);
		return parent[p];
	}

	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}

	void unionElements(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);

		if (pRoot == qRoot)
			return;
		// �����3���Ż��ĵ������֮ǰ��size, ���ڿ�rank
		if (rank[pRoot] < rank[qRoot]) {
			parent[pRoot] = qRoot;
		}
		else if (rank[qRoot] < rank[pRoot]) {
			parent[qRoot] = pRoot;

		}
		else {  // rank[pRoot] == rank[qRoot]
			parent[pRoot] = qRoot;
			rank[qRoot] += 1;
		}

	}
};

// ElogE + ElogV ??
template<typename Graph, typename Weight>
class KruskalMST {
private:
	vector<Edge<Weight>> mst;
	Weight mstWeight;
public:
	KruskalMST(Graph& graph) {
		MinHeap<Edge<Weight>> pq(graph.E());
		for (int i = 0; i < graph.V(); i++)
		{
			typename Graph::adjIterator adj(graph, i);
			for (Edge<Weight>*e = adj.begin(); !adj.end(); e = adj.next()) {
			   if (e->v() < e->w()) // v��w������ȣ���˻��ǵ�������ȥ�ء�
				   pq.insert(*e);
			}
		}
		UnionFind uf(graph.V());
		while (!pq.isEmpty()&& mst.size()< graph.V()-1) {

		   Edge<Weight> e =pq.extractMin();
		   if (uf.isConnected(e.v(), e.w()))
			   continue;
		   mst.push_back(e);
		   uf.unionElements(e.v(), e.w());

		}

		mstWeight = mst[0].wt();
		for (int i = 1; i < mst.size(); i++)
			mstWeight += mst[i].wt();


	}
	~KruskalMST() {

	}

	vector<Edge<Weight>> mstEdges() {
		return mst;
	}

	Weight result() {
		return mstWeight;
	}
};


// �ܽ᣺
/*
  Lazy Prim: O(ElogE)
  Prim : O(ElogV)  ��Ŀǰ��֪���ţ�����һ���Ǿ������ţ����ܻ��и���Ч���㷨�� 
  Kruskal: O(ElogE)
*/
/*
   ������б�����ȵıߣ���ʱ����ͼ���ܴ��ڶ����С������������Щ��С��������Ȩֵ��һ���ġ�
   ����һ������С���������㷨 Vyssotsky's Algorithm �������𽥵���ӵ��������У�һ���γɻ���ɾ������Ȩֵ���ıߡ�
*/