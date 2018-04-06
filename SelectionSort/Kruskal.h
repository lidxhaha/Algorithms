#pragma once
#include<cassert>
#include "MinHeap.h"
#include<vector>
class UnionFind {

private:
	int* parent;
	int* rank;   // rank[i]表示以i为根的集合中树的最大深度（树的层数）
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

	// 返回节点p的根
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
		// 相较于3，优化的点在这里，之前看size, 现在看rank
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
			   if (e->v() < e->w()) // v和w不会相等，如此机智地做到了去重。
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


// 总结：
/*
  Lazy Prim: O(ElogE)
  Prim : O(ElogV)  （目前已知最优，但不一定是绝对最优，可能会有更高效的算法） 
  Kruskal: O(ElogE)
*/
/*
   如果横切边有相等的边，此时，此图可能存在多个最小生成树，但这些最小生成树的权值是一样的。
   还有一种求最小生成树的算法 Vyssotsky's Algorithm ：将边逐渐地添加到生成树中，一旦形成环，删除环中权值最大的边。
*/