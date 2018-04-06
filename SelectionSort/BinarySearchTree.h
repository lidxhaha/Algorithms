#pragma once
#include<queue>
#include<cassert>
// 二分查找法，在有序数组arr中，查找target
// 时间复杂度O（log n）,极端情况下可退化到O（n)
// 如果找到target, 返回相应的索引index
// 如果没有找到target,则返回-1
template<typename T>
int binarySearch(T arr[], int n, T target) {

	// 在arr[l...r]之中查找target
	int l = 0, r = n - 1;
	while (l <= r){
        
		// int mid = (l + r) / 2;  // l+r有可能溢出,两个整数相加时，都要考虑这个问题？
		int mid = l + (r - l) / 2;
		if (arr[mid] == target)
			return mid;
		// 在arr[l ... mid-1]之中查找target,因为mid位置已经不可能找到target了。
		if (target < arr[mid])  // 证明target 在位置mid的左边
			r = mid - 1;
		else           // 在arr[mid+1 ... r]之中查找target
			l = mid + 1;
	}
	return -1;

}

// 用递归法来实现二分查找（递归二分查找略差于非递归）

// 写出针对二分查找时要查找的元素有多个重复值的情况的floor和ceil


// Binary Search Tree
// 在二分搜索树中添加，查找，插入，删除一个元素的时间复杂度都是O（log n)
// 二分搜索树在极端情况下可退化成链表，此时各种时间复杂度会退化为 O(n)
template<typename Key, typename Value>
class BST {
public:
	BST() {
		root = NULL;
		count = 0;
	}

	// 用后序遍历的方式来销毁整颗二叉搜索树
	~BST() {
		destroy(root);
	}

	int size() {
		return count;
	}

	bool isEmpty() {
		return count == 0;
	}

	void insert(Key key, Value value) {
		root = insert(root, key, value);
	}

	bool contain(Key key) {
		return contain(root, key);
	}

	//关键在于考虑到如果二叉搜索树中不存在key该如何处理，所以选择返回指针，因为指针可以为NULL
	Value * search(Key key) {
		return search(root, key);
	}

	// 以下四种遍历，由于每个节点都访问了常数次，所以它们的时间复杂度都是O（n）
	// 前序遍历
	void preOrder() {
		preOrder(root);
	}

	//中序遍历
	void inOrder() {
		inOrder(root);
	}

	//后序遍历
	void postOrder() {
		postOrder(root);
	}

	// 层序遍历，广度优先遍历
	void levelOrder() {
		queue<Node*> q;
		q.push(root);
		while (!q.empty()) {
			Node* node = q.front();
			q.pop();
			cout << node->key << endl;
			if (node->left)
				q.push(node->left);
			if (node->right)
				q.push(node->right);
		}
	}

	// 寻找最小的键值
	Key minimum() {
		assert(count != 0);
		Node* minNode = minimum(root);
		return minNode->key;
	}

	// 寻找最大的键值
	Key maximum() {
		assert(count != 0);
		Node* maxNode = maximum(root);
		return maxNode->key;
	}

	// 从二叉树中删除最小值所在节点
	void removeMin() {
		if (root)
			root = removeMin(root);
	}

	// 从二叉树中删除最大值所在的节点
	void removeMax() {
		if (root)
			root = removeMax(root);
	}


	//从二叉树中删除键值为key的节点
	// 采用Hubbard Deletion算法，处理要删除的节点既有左孩子又有右孩子时，将右子树中最小的节点
	//替换要删除的节点，同时将该最小节点删除。
	void remove(Key key) {
		root = remove(root, key);
	}


	// 1.二分搜索树遗留问题：考虑二叉树的键值按顺序输出后，其前驱和后继是谁（predecessor, successor）
	// 2.以及floor 和 ceil函数的实现（该元素存在时floor和ceil就是其自身，不存在时，按排好的顺序
	// 找出其前一个和后一个元素。（用递归实现）
	// 3. rank，select的编程
	// rank: 元素58是排名第几的元素？ select:排名第10的元素是谁？
    

private:
	struct Node {
		Key key;
		Value value;
		Node *left;
		Node *right;
		Node(Key key, Value value) {
			this->key = key;
			this->value = value;
			this->left = this->right = NULL;
		}
		// 复制某个节点
		Node(Node *node) {
			this->key = node->key;
			this->value = node->value;
			this->left = node->left;
			this->right = node->right;
		}
	};

	Node * root;
	int count;
	// 向以node为根的二叉搜索树中，插入节点（key, value)
	// 返回插入新节点后的二叉搜索树的根
	Node * insert(Node * node, Key key, Value value) {
     
		// 要增加一个节点
		if (node == NULL) {
			count++;
			return new Node(key, value); // 其实返回值的作用体现在这里
		}
		// 更新键所对应的值
		if (key == node->key)
			node->value = value;
		// 继续往左孩子或右孩子的方向递归
		else if (key < node->key)
			node->left = insert(node->left, key, value);
		else  // key > node-> key
			node->right = insert(node->right, key, value);
		return node; // 这里只是不得不返回一个值了

	}

	// 问，insert的非递归实现？

	// 查看以node为根的二叉搜索树中是否包含键值为key的节点
	bool contain(Node* node, Key key) {
		
		if (node == NULL)
			return false;
		if (key == node->key)
			return true;
		else if (key < node->key)
			return contain(node->left, key);
		else
			return contain(node->right, key);
	}

	// 在以node为根的二叉搜索树中查找Key所对应的Value
	Value* search(Node* node, Key key) {
		if (node == NULL)
			return NULL;
		if (key == node->key)
			return &(node->value);
		else if (key < node->key)
			return search(node->left, key);
		else
			return search(node->right, key);
	}

	// 对以node为根的二叉搜索树进行前序遍历
	void preOrder(Node* node) {
		if (node != NULL)
		{
			cout << node->key << endl;
			preOrder(node->left);
			preOrder(node->right);
		}
	}

	// 对以node为根的二叉搜索树进行中序遍历
	void inOrder(Node* node) {
		if (node != NULL)
		{	
			inOrder(node->left);
			cout << node->key << endl;
			inOrder(node->right);
		}
	}

	// 对以node为根的二叉搜索树进行后序遍历
	void postOrder(Node* node) {
		if (node != NULL)
		{
			postOrder(node->left);
			postOrder(node->right);
			cout << node->key << endl;
		}
	}

	void destroy(Node* node) {
		if (node != NULL) {
			destroy(node->left);
			destroy(node->right);
			delete node;
			count--;
		}
	}

	//在以node为根的二叉搜索树中，返回最小键值的节点
	Node* minimum(Node* node) {

		if (node->left == NULL) 
			return node;
		else
			return minimum(node->left);
	}

	//在以node为根的二叉搜索树中，返回最大键值的节点
	Node* maximum(Node* node) {
		if (node->right == NULL)
			return node;
		else
			return maximum(node->right);
	}

	// 删除掉以node为根的二分搜索树中的最小节点
	// 返回删除节点后新的二分搜索树的根
	Node* removeMin(Node* node) {
		if (node->left == NULL)
		{
			Node* rightNode = node->right; // node->right 为NULL时也是OK的
			delete node;
			count--;
			return rightNode;
		}
		node->left = removeMin(node->left);
		return node;
	}

	// 删除掉以node为根的二分搜索树中的最大节点
	// 返回删除节点后新的二分搜索树的根
	Node* removeMax(Node* node) {
		if (node->right == NULL) {
			Node* leftNode = node->left;
			delete node;
			count--;
			return leftNode;
		}
		node->right = removeMax(node->right);
		return node;

	}

	// 删除掉以node为根的二分搜索树中键值为key的节点
	// 返回删除节点后新的二分搜索树的根
	Node* remove(Node* node, Key key) {
		if (node == NULL)
			return NULL;
		
		if (key < node->key) {
			node->left = remove(node->left, key);
			return node;
		}
		else if (key > node->key) {
			node->right = remove(node->right, key);
			return node;
		}
		else {      // key == node->key

			//左右孩子都为空，仍然OK 

			if (node->left == NULL) {
				Node* rightNode = node->right;
				delete node;
				count--;
				return rightNode;
			}

			if (node->right == NULL) {
				Node* leftNode = node->left;
				delete node;
				count--;
				return leftNode;
			}

			// node->left != NULL && node->right != NULL
			// 之所以复制一份是因为minimum(node->right)马上要被删除了
			Node* successor = new Node(minimum(node->right));  // 保存最小的节点
			count++;
			successor->right = removeMin(node->right);  //删除最小的节点
			successor->left = node->left;
			delete node;
			count--;
			return successor;
		}

	}



};
