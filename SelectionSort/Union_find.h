#pragma once
#include<cassert>
class UnionFind1 {
public:
	UnionFind1(int n) {
		count = n;
		id = new int[n];
		for (int i = 0; i < n;i++) {  //初始认为任何两个节点都没有连接到一起
			id[i] = i;
		}
	}

	~UnionFind1() {
		delete[] id;
	}

	int find(int p) {
		assert(p >= 0 && p < count);
		return id[p];
	}

	// 查的操作，时间复杂度是O（1）
	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}

	// 并的操作，时间复杂度是O（n)
	void unionElements(int p, int q) {
		int pID = find(p);
		int qID = find(q);

		if (pID == qID)
			return;

		for (int i = 0; i < count; i++)
			if (id[i] == pID)
				id[i] = qID;

	}
private:
	int* id;
	int count;

};

// 用指向自己的父亲的方式进行优化（具体实现上并没有真正用到指针，只是借助了这种指向的思想）
// 数组parent的含义变成了自己的父节点是谁，而不是之前的含义了。
class UnionFind2 {

private:
	int* parent;
	int count;

public:
	UnionFind2(int count) {
		parent = new int[count];
		this->count = count;
		for (int i = 0; i < count; i++)
			parent[i] = i;
	}

	~UnionFind2() {
		delete[] parent;
	}
	
	// 返回节点p的根
	int find(int p) {
		assert(p >= 0 && p < count);
		while (p != parent[p])
			p = parent[p];
		return p;
	}

	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}

	//如此并的操作就很简单了
	void unionElements(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);

		if (pRoot == qRoot)
			return;
		parent[pRoot] = qRoot;
	}
};

// 在2的基础上，在处理“并”操作时，基于size进行优化。
//  (实测结果3比2有很大的一个提升)
class UnionFind3 {

private:
	int* parent;
	int* sz;   // sz[i]表示以i为根的集合中元素的个数
	int count;

public:
	UnionFind3(int count) {
		parent = new int[count];
		sz = new int[count];
		this->count = count;
		for (int i = 0; i < count; i++) {
			parent[i] = i;
			sz[i] = 1;
		}
	
	}

	~UnionFind3() {
		delete[] parent;
		delete[] sz;
	}

	// 返回节点p的根
	int find(int p) {
		assert(p >= 0 && p < count);
		while (p != parent[p])
			p = parent[p];
		return p;
	}

	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}

	void unionElements(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);

		if (pRoot == qRoot)
			return;
		// 相较于2，优化的点在这里（让元素少的集合并到元素多的集合上）
		// 与根pRoot相连的元素较少，让pRoot指向qRoot
		// 这样做避免了构建太长的一串数（树的层数更少），让find操作的速度大大加快
		if (sz[pRoot] < sz[qRoot]) {
			parent[pRoot] = qRoot;
			sz[qRoot] += sz[pRoot];
		}
		else {
			parent[qRoot] = pRoot;
			sz[pRoot] += sz[qRoot];
		}
		
	}
};

class UnionFind4 {

private:
	int* parent;
	int* rank;   // rank[i]表示以i为根的集合中树的最大深度（树的层数）
	int  count;

public:
	UnionFind4(int count) {
		parent = new int[count];
	    rank = new int[count];
		this->count = count;
		for (int i = 0; i < count; i++) {
			parent[i] = i;
			rank[i] = 1;
		}

	}

	~UnionFind4() {
		delete[] parent;
		delete[] rank;
	}

	// 返回节点p的根
	int find(int p) {
		assert(p >= 0 && p < count);
		while (p != parent[p])
			p = parent[p];
		return p;
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
		else if (rank[qRoot] < rank[pRoot]){
			parent[qRoot] = pRoot;
		
		}
		else {  // rank[pRoot] == rank[qRoot]
			parent[pRoot] = qRoot;
			rank[qRoot] += 1;
		}

	}
};



// 基于路径压缩（path compression）的优化

class UnionFind5 {

private:
	int* parent;
	int* rank;   // rank[i]表示以i为根的集合中树的最大深度（树的层数）
	int  count;

public:
	UnionFind5(int count) {
		parent = new int[count];
		rank = new int[count];
		this->count = count;
		for (int i = 0; i < count; i++) {
			parent[i] = i;
			rank[i] = 1;
		}

	}

	~UnionFind5() {
		delete[] parent;
		delete[] rank;
	}

	// 返回节点p的根
	int find(int p) {
		assert(p >= 0 && p < count);

	// 第一个版本的路径压缩， 二跳法
	//	while (p != parent[p]) {
			// 路径压缩算法的体现（相当于以前每次走一步，现在两步并做一步走）
		//	parent[p] = parent[parent[p]];
		//	p = parent[p];
		//}
	
	// 第二个版本的路径压缩，指向根节点法（理论上这个最优，但因为有递归的额外开销，所以和
	// 第一个版本的路径压缩差不多）
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

// 经过路径压缩等一系列操作后，并查集的操作，时间复杂度近乎都是O（1）的。






