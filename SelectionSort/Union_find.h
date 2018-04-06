#pragma once
#include<cassert>
class UnionFind1 {
public:
	UnionFind1(int n) {
		count = n;
		id = new int[n];
		for (int i = 0; i < n;i++) {  //��ʼ��Ϊ�κ������ڵ㶼û�����ӵ�һ��
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

	// ��Ĳ�����ʱ�临�Ӷ���O��1��
	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}

	// ���Ĳ�����ʱ�临�Ӷ���O��n)
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

// ��ָ���Լ��ĸ��׵ķ�ʽ�����Ż�������ʵ���ϲ�û�������õ�ָ�룬ֻ�ǽ���������ָ���˼�룩
// ����parent�ĺ��������Լ��ĸ��ڵ���˭��������֮ǰ�ĺ����ˡ�
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
	
	// ���ؽڵ�p�ĸ�
	int find(int p) {
		assert(p >= 0 && p < count);
		while (p != parent[p])
			p = parent[p];
		return p;
	}

	bool isConnected(int p, int q) {
		return find(p) == find(q);
	}

	//��˲��Ĳ����ͺܼ���
	void unionElements(int p, int q) {
		int pRoot = find(p);
		int qRoot = find(q);

		if (pRoot == qRoot)
			return;
		parent[pRoot] = qRoot;
	}
};

// ��2�Ļ����ϣ��ڴ�����������ʱ������size�����Ż���
//  (ʵ����3��2�кܴ��һ������)
class UnionFind3 {

private:
	int* parent;
	int* sz;   // sz[i]��ʾ��iΪ���ļ�����Ԫ�صĸ���
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

	// ���ؽڵ�p�ĸ�
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
		// �����2���Ż��ĵ��������Ԫ���ٵļ��ϲ���Ԫ�ض�ļ����ϣ�
		// ���pRoot������Ԫ�ؽ��٣���pRootָ��qRoot
		// �����������˹���̫����һ���������Ĳ������٣�����find�������ٶȴ��ӿ�
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
	int* rank;   // rank[i]��ʾ��iΪ���ļ��������������ȣ����Ĳ�����
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

	// ���ؽڵ�p�ĸ�
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
		// �����3���Ż��ĵ������֮ǰ��size, ���ڿ�rank
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



// ����·��ѹ����path compression�����Ż�

class UnionFind5 {

private:
	int* parent;
	int* rank;   // rank[i]��ʾ��iΪ���ļ��������������ȣ����Ĳ�����
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

	// ���ؽڵ�p�ĸ�
	int find(int p) {
		assert(p >= 0 && p < count);

	// ��һ���汾��·��ѹ���� ������
	//	while (p != parent[p]) {
			// ·��ѹ���㷨�����֣��൱����ǰÿ����һ����������������һ���ߣ�
		//	parent[p] = parent[parent[p]];
		//	p = parent[p];
		//}
	
	// �ڶ����汾��·��ѹ����ָ����ڵ㷨��������������ţ�����Ϊ�еݹ�Ķ��⿪�������Ժ�
	// ��һ���汾��·��ѹ����ࣩ
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

// ����·��ѹ����һϵ�в����󣬲��鼯�Ĳ�����ʱ�临�ӶȽ�������O��1���ġ�






