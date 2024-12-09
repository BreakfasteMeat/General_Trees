#include <cstdlib>

struct node {
	node** children;
	int num_child;
	node* parent;
	int elem;

	node() {
		children = (node**)calloc(10, sizeof(node*));
		num_child = 0;
		parent = NULL;
	}
	int depth() {
		if (parent == NULL) {
			return 0;
		}
		return 1 + parent->depth();
	}


	int height() {
		if (num_child == 0) {
			return 0;
		}
		else {
			int max = 0;

			for (int i = 0; i < num_child; i++) {
				if (max < children[i]->height())
					max = children[i]->height();
			}
			return 1 + max;
		}
		return -1;
	}
};