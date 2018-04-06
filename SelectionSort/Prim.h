#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"
#include "MinHeap.h"
#include "IndexMinHeap.h"

// 最小生成树 Minimum Span Tree
// Lazy Prime的时间复杂度是O（ElogE)
template<typename Graph, typename Weight>
class LazyPrimMST {
private:
	Graph & G;
	MinHeap<Edge<Weight>> pq; // prioriy queue
	bool * marked;
	vector< Edge<Weight> > mst; // 存储最小生成树对应的边
	Weight mstWeight;  // 存储最小权值
	void visit(int v) {
		assert(!marked[v]);
		marked[v] = true;
		typename Graph::adjIterator adj(G, v);
		for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next())
			if (!marked[e->other(v)]) // 另一个边没有被访问过
				pq.insert(*e);

	}
public:
	     //  相当于最小堆的模板类型是Edge<Weight>
	     // MinHeap<Edge<Weight>>(graph.E()) 相当于用graph.E()初始化一个最小堆类
	     // 用pq(graph.E())也可以（区别在于一个用拷贝构造函数，一个用构造函数）
	     LazyPrimMST(Graph& graph) :G(graph), pq(MinHeap<Edge<Weight>>(graph.E())) // 按边数开空间
	    {
		   marked = new bool[G.V()];
		   for (int i = 0; i < G.V(); i++)
			   marked[i] = false;
		   mst.clear(); //vector类初始化一下比较保险

		   // Lazy Prim
		   visit(0);
		   while (!pq.isEmpty()) // 在最小堆的数据没有排空时就一直循环
		   {
			   Edge<Weight> e = pq.extractMin();
			   if (marked[e.v()] == marked[e.w()]) // 在同一侧，根本不是横切边
				   continue;
			   mst.push_back(e);
			   if (!marked[e.v()]) // 总会有一个边还没被访问过
				   visit(e.v());
			   else
				   visit(e.w());
		   }

		   mstWeight = mst[0].wt();
		   for (int i = 1; i < mst.size(); i++)
			   mstWeight += mst[i].wt();
    	}
	
		~LazyPrimMST() {
			delete[] marked;
	   }

		vector<Edge<Weight>> mstEdges() {
			return mst;
		}

		Weight result() {
			return mstWeight;
		}

};


// 时间复杂度 ElogV  //不太理解
template<typename Graph, typename Weight>
class PrimMST {
private:
	Graph & G;
	IndexMinHeap<Weight> ipq; // 注意此处与LazyPrim的区别
	vector<Edge<Weight>*> edgeTo; // edgeTo存储的是到某个顶点的最小边的指针，由此堆中的元素变为了V个，时间复杂度得以优化
	bool * marked;
	vector<Edge<Weight>> mst;
	Weight mstWeight;

	void visit(int v) {
		assert(!marked[v]);
		marked[v] = true;
		typename Graph::adjIterator adj(G, v);
		for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next())
		{
			int w = e->other(v);
			if (!marked[w]) {
				if (!edgeTo[w])  
				{
					ipq.insert(w, e->wt());
					edgeTo[w] = e;
				}
				else if (e->wt() < edgeTo[w]->wt()) {
					edgeTo[w] = e;
					ipq.change(w, e->wt());
				}
			}
		}
	}
public:      // IndexMinHeap<Weight>(graph.V())
	PrimMST(Graph &graph) :G(graph), ipq((graph.V())) // 开顶点个数的空间
	{
		marked = new bool[G.V()];
		for (int i = 0; i < G.V(); i++) {
			marked[i] = false;
			edgeTo.push_back(NULL);
		}
		mst.clear();

		// Prim
		visit(0);
		while (!ipq.isEmpty())
		{
			int v = ipq.extractMinIndex();
			assert(edgeTo[v]);
			mst.push_back(*edgeTo[v]);
			visit(v);
		}

		mstWeight = mst[0].wt();
		for (int i = 1; i < mst.size(); i++)
			mstWeight += mst[i].wt();

	}

	~PrimMST() {
		delete[] marked;
	}

	vector<Edge<Weight>> mstEdges() {
		return mst;
	}

	Weight result() {
		return mstWeight;
	}

};


