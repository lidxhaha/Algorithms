#pragma once
#include<queue>
#include<cassert>
// ���ֲ��ҷ�������������arr�У�����target
// ʱ�临�Ӷ�O��log n��,��������¿��˻���O��n)
// ����ҵ�target, ������Ӧ������index
// ���û���ҵ�target,�򷵻�-1
template<typename T>
int binarySearch(T arr[], int n, T target) {

	// ��arr[l...r]֮�в���target
	int l = 0, r = n - 1;
	while (l <= r){
        
		// int mid = (l + r) / 2;  // l+r�п������,�����������ʱ����Ҫ����������⣿
		int mid = l + (r - l) / 2;
		if (arr[mid] == target)
			return mid;
		// ��arr[l ... mid-1]֮�в���target,��Ϊmidλ���Ѿ��������ҵ�target�ˡ�
		if (target < arr[mid])  // ֤��target ��λ��mid�����
			r = mid - 1;
		else           // ��arr[mid+1 ... r]֮�в���target
			l = mid + 1;
	}
	return -1;

}

// �õݹ鷨��ʵ�ֶ��ֲ��ң��ݹ���ֲ����Բ��ڷǵݹ飩

// д����Զ��ֲ���ʱҪ���ҵ�Ԫ���ж���ظ�ֵ�������floor��ceil


// Binary Search Tree
// �ڶ�������������ӣ����ң����룬ɾ��һ��Ԫ�ص�ʱ�临�Ӷȶ���O��log n)
// �����������ڼ�������¿��˻���������ʱ����ʱ�临�ӶȻ��˻�Ϊ O(n)
template<typename Key, typename Value>
class BST {
public:
	BST() {
		root = NULL;
		count = 0;
	}

	// �ú�������ķ�ʽ���������Ŷ���������
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

	//�ؼ����ڿ��ǵ���������������в�����key����δ�������ѡ�񷵻�ָ�룬��Ϊָ�����ΪNULL
	Value * search(Key key) {
		return search(root, key);
	}

	// �������ֱ���������ÿ���ڵ㶼�����˳����Σ��������ǵ�ʱ�临�Ӷȶ���O��n��
	// ǰ�����
	void preOrder() {
		preOrder(root);
	}

	//�������
	void inOrder() {
		inOrder(root);
	}

	//�������
	void postOrder() {
		postOrder(root);
	}

	// ���������������ȱ���
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

	// Ѱ����С�ļ�ֵ
	Key minimum() {
		assert(count != 0);
		Node* minNode = minimum(root);
		return minNode->key;
	}

	// Ѱ�����ļ�ֵ
	Key maximum() {
		assert(count != 0);
		Node* maxNode = maximum(root);
		return maxNode->key;
	}

	// �Ӷ�������ɾ����Сֵ���ڽڵ�
	void removeMin() {
		if (root)
			root = removeMin(root);
	}

	// �Ӷ�������ɾ�����ֵ���ڵĽڵ�
	void removeMax() {
		if (root)
			root = removeMax(root);
	}


	//�Ӷ�������ɾ����ֵΪkey�Ľڵ�
	// ����Hubbard Deletion�㷨������Ҫɾ���Ľڵ�������������Һ���ʱ��������������С�Ľڵ�
	//�滻Ҫɾ���Ľڵ㣬ͬʱ������С�ڵ�ɾ����
	void remove(Key key) {
		root = remove(root, key);
	}


	// 1.�����������������⣺���Ƕ������ļ�ֵ��˳���������ǰ���ͺ����˭��predecessor, successor��
	// 2.�Լ�floor �� ceil������ʵ�֣���Ԫ�ش���ʱfloor��ceil����������������ʱ�����źõ�˳��
	// �ҳ���ǰһ���ͺ�һ��Ԫ�ء����õݹ�ʵ�֣�
	// 3. rank��select�ı��
	// rank: Ԫ��58�������ڼ���Ԫ�أ� select:������10��Ԫ����˭��
    

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
		// ����ĳ���ڵ�
		Node(Node *node) {
			this->key = node->key;
			this->value = node->value;
			this->left = node->left;
			this->right = node->right;
		}
	};

	Node * root;
	int count;
	// ����nodeΪ���Ķ����������У�����ڵ㣨key, value)
	// ���ز����½ڵ��Ķ����������ĸ�
	Node * insert(Node * node, Key key, Value value) {
     
		// Ҫ����һ���ڵ�
		if (node == NULL) {
			count++;
			return new Node(key, value); // ��ʵ����ֵ����������������
		}
		// ���¼�����Ӧ��ֵ
		if (key == node->key)
			node->value = value;
		// ���������ӻ��Һ��ӵķ���ݹ�
		else if (key < node->key)
			node->left = insert(node->left, key, value);
		else  // key > node-> key
			node->right = insert(node->right, key, value);
		return node; // ����ֻ�ǲ��ò�����һ��ֵ��

	}

	// �ʣ�insert�ķǵݹ�ʵ�֣�

	// �鿴��nodeΪ���Ķ������������Ƿ������ֵΪkey�Ľڵ�
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

	// ����nodeΪ���Ķ����������в���Key����Ӧ��Value
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

	// ����nodeΪ���Ķ�������������ǰ�����
	void preOrder(Node* node) {
		if (node != NULL)
		{
			cout << node->key << endl;
			preOrder(node->left);
			preOrder(node->right);
		}
	}

	// ����nodeΪ���Ķ��������������������
	void inOrder(Node* node) {
		if (node != NULL)
		{	
			inOrder(node->left);
			cout << node->key << endl;
			inOrder(node->right);
		}
	}

	// ����nodeΪ���Ķ������������к������
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

	//����nodeΪ���Ķ����������У�������С��ֵ�Ľڵ�
	Node* minimum(Node* node) {

		if (node->left == NULL) 
			return node;
		else
			return minimum(node->left);
	}

	//����nodeΪ���Ķ����������У���������ֵ�Ľڵ�
	Node* maximum(Node* node) {
		if (node->right == NULL)
			return node;
		else
			return maximum(node->right);
	}

	// ɾ������nodeΪ���Ķ����������е���С�ڵ�
	// ����ɾ���ڵ���µĶ����������ĸ�
	Node* removeMin(Node* node) {
		if (node->left == NULL)
		{
			Node* rightNode = node->right; // node->right ΪNULLʱҲ��OK��
			delete node;
			count--;
			return rightNode;
		}
		node->left = removeMin(node->left);
		return node;
	}

	// ɾ������nodeΪ���Ķ����������е����ڵ�
	// ����ɾ���ڵ���µĶ����������ĸ�
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

	// ɾ������nodeΪ���Ķ����������м�ֵΪkey�Ľڵ�
	// ����ɾ���ڵ���µĶ����������ĸ�
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

			//���Һ��Ӷ�Ϊ�գ���ȻOK 

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
			// ֮���Ը���һ������Ϊminimum(node->right)����Ҫ��ɾ����
			Node* successor = new Node(minimum(node->right));  // ������С�Ľڵ�
			count++;
			successor->right = removeMin(node->right);  //ɾ����С�Ľڵ�
			successor->left = node->left;
			delete node;
			count--;
			return successor;
		}

	}



};
