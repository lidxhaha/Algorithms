#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include "Edge.h"
#include "MinHeap.h"
#include "IndexMinHeap.h"

// ��С������ Minimum Span Tree
// Lazy Prime��ʱ�临�Ӷ���O��ElogE)
template<typename Graph, typename Weight>
class LazyPrimMST {
private:
	Graph & G;
	MinHeap<Edge<Weight>> pq; // prioriy queue
	bool * marked;
	vector< Edge<Weight> > mst; // �洢��С��������Ӧ�ı�
	Weight mstWeight;  // �洢��СȨֵ
	void visit(int v) {
		assert(!marked[v]);
		marked[v] = true;
		typename Graph::adjIterator adj(G, v);
		for (Edge<Weight>* e = adj.begin(); !adj.end(); e = adj.next())
			if (!marked[e->other(v)]) // ��һ����û�б����ʹ�
				pq.insert(*e);

	}
public:
	     //  �൱����С�ѵ�ģ��������Edge<Weight>
	     // MinHeap<Edge<Weight>>(graph.E()) �൱����graph.E()��ʼ��һ����С����
	     // ��pq(graph.E())Ҳ���ԣ���������һ���ÿ������캯����һ���ù��캯����
	     LazyPrimMST(Graph& graph) :G(graph), pq(MinHeap<Edge<Weight>>(graph.E())) // ���������ռ�
	    {
		   marked = new bool[G.V()];
		   for (int i = 0; i < G.V(); i++)
			   marked[i] = false;
		   mst.clear(); //vector���ʼ��һ�±Ƚϱ���

		   // Lazy Prim
		   visit(0);
		   while (!pq.isEmpty()) // ����С�ѵ�����û���ſ�ʱ��һֱѭ��
		   {
			   Edge<Weight> e = pq.extractMin();
			   if (marked[e.v()] == marked[e.w()]) // ��ͬһ�࣬�������Ǻ��б�
				   continue;
			   mst.push_back(e);
			   if (!marked[e.v()]) // �ܻ���һ���߻�û�����ʹ�
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


// ʱ�临�Ӷ� ElogV  //��̫���
template<typename Graph, typename Weight>
class PrimMST {
private:
	Graph & G;
	IndexMinHeap<Weight> ipq; // ע��˴���LazyPrim������
	vector<Edge<Weight>*> edgeTo; // edgeTo�洢���ǵ�ĳ���������С�ߵ�ָ�룬�ɴ˶��е�Ԫ�ر�Ϊ��V����ʱ�临�Ӷȵ����Ż�
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
	PrimMST(Graph &graph) :G(graph), ipq((graph.V())) // ����������Ŀռ�
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


