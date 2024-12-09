#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>
#include "gentree.h"
using namespace std;

class MyGenTree : public GenTree {
	node* root;
	int size;

public:
	node* addRoot(int e) {
		if (root != NULL) {
			throw logic_error("Already has root");
		}
		node* n = new node();
		n->elem = e;
		size++;
		root = n;
		return n;
	}

	node* addChild(node* p, int e) {
		node* n = new node();
		n->elem = e;
		n->parent = p;
		p->children[(p->num_child)++] = n;
		size++;
		return n;
	}


	void remove(node* n) {
		if (n->num_child != 0) {
			throw logic_error(to_string(n->elem) + " has children");
		}
		if (n == root && size == 1) {
			root = NULL;
			free(n);
			size--;
		}
		else {
			node* parent_node = n->parent;
			int i = 0;
			for (i = 0; i < parent_node->num_child; i++) {
				if (parent_node->children[i] == n) break;
			}

			for (i; i < parent_node->num_child; i++) {
				parent_node->children[i] = parent_node->children[i + 1];
			}
			(parent_node->num_child)--;
			size--;
			n->parent = NULL;
			free(n);

		}
	}
	void BFS() {
		queue<node*> node_queue;
		node_queue.push(root);
		while (!node_queue.empty()) {
			node* curr = node_queue.front();
			node_queue.pop();
			cout << curr->elem << " ";
			for (int i = 0; i < curr->num_child; i++) {
				node_queue.push(curr->children[i]);
			}
		}
	}

	void DFS() {
		cout << "PREORDER DFS:" << endl;
		preorder();
		cout << endl;
		cout << "POSTORDER DFS: " << endl;
		postorder();
		cout << endl;

	}
	void postorder() {
		postorder_recursive(root);
	}
	void postorder_recursive(node* n) {
		if (n == NULL) {
			return;
		}
		for (int i = 0; i < n->num_child; i++) {
			postorder_recursive(n->children[i]);
		}
		cout << n->elem << " ";
	}
	void preorder() {
		preorder_recursive(root);
	}
	void preorder_recursive(node* n) {
		if (n == NULL) {
			return;
		}
		cout << n->elem << " ";
		for (int i = 0; i < n->num_child; i++) {
			preorder_recursive(n->children[i]);
		}
	}
	int nodes_num() {
		return nodes_num_recursive(root);
	}
	int nodes_num_recursive(node* n) {
		int sum = 1;
		for (int i = 0; i < n->num_child; i++) {
			sum += nodes_num_recursive(n->children[i]);
		}
		return sum;
	}

	int getSize() {
		return size;
	}

	node* getRoot() {
		return root;
	}
};