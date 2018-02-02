#include <stdio.h>
#include <stdlib.h>

typedef long long int Llint;

typedef struct N
{
	Llint v;
	struct N* parent;
	struct N* left;
	struct N* right;
} Node;

/*
 Makes a new tree with data vert and left, right subtrees as t1, t2.
 return: pointer to root.
 */
Node* join_trees(Node* t1, Node* t2, Llint vert) {
	Node* root = (Node*)malloc(sizeof(Node));
	root->parent = NULL;
	root->v = vert;
	root->left = t1;
	root->right = t2;

	return root;
}
/*
Node* insert_Node(Node* head, Llint dat) {
	Node* i;
	i = head;
	Node* child = join_trees(NULL, NULL, dat);
	while(1==1) {

		if(i.v > dat) {
			if(i->left != NULL) {
				i = i->left;
				continue;
			}
			i->left = child;
		}
		if(i.v <= dat) {
			if(i->right != NULL) {
				i = i->right;
				continue;
			}
			i->right = child;
		}
		break;
	}
	return head;
}*/
Node * insert_Node(Node * head, Llint dat)
{
	if(head == NULL)
		head = join_trees(NULL, NULL, dat);
	else if(head->v > dat)
		head->left = insert_Node(head->left, dat);
	else
		head->right = insert_Node(head->right, dat);
	return head;
}

void in_print(Node* head) {
	if(head->left != NULL)
		in_print(head->left);
	printf("%lld ", head->v);
	if(head->right!=NULL)
		in_print(head->right);
	return;
}

Llint search(Node* head, Llint key) {
	if(head->v == key) {
		return 1;
	}
	else if(key < head->v) {
		if(head->left != NULL)
			return search(head->left, key);
		else
			return 0;
	}
	else if(key > head->v) {
		if(head->right != NULL)
			return search(head->right, key);
		else
			return 0;
	}
}

Node * succ(Node* head) {
	
}

Llint dfs(Node* head, Llint key) {

}

int main() {
	Node* bl = join_trees(NULL, NULL, 50);
	Llint datar;
	for (Llint i = 0; i < 100; ++i)
	{
		scanf("%lld", &datar);
		bl = insert_Node(bl, datar);
		in_print(bl);
		printf("\nSearch for : ");
		scanf("%lld", &datar);
		printf("%lld\n", search(bl, datar));
	}

	return 0;
}
