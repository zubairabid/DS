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

Node * tree_minimum(Node * base) {
	Node * tmp = base->right;
	if(base->right == NULL) {
		return base;
	}
	else {
		while(tmp->left != NULL) {
			tmp = tmp->left;
		}
		return tmp;
	}
}

Node * successor(Node * base) {
	Llint dat = base->v;
	if(base->right != NULL) { // We can look in the subtree
		return tree_minimum(base);
	}
	else { // we look up
		Node * temp = base->parent;
		while(temp!=NULL && temp->v < dat) { // <=?
			base = temp;
			temp = base->parent;
		}
		return temp;
	}
}

// TODO TODO TODO TODO TODO TODO
// TODO TODO TODO TODO TODO TODO
// TODO TODO TODO TODO TODO TODO
// TODO TODO TODO TODO TODO TODO
// TODO TODO TODO TODO TODO TODO
// TODO TODO TODO TODO TODO TODO
// TODO TODO TODO TODO TODO TODO
// THe root passed to the function is the tree head.
Node * delete(Node* root, Llint val) { // the head has to be the overall tree head !!!! RECONSIDER. Make it the parent
	if(root == NULL) {
		return NULL;
	}
	else if (root->v == val) {
		Node * p = root->parent;
		if (root->right == NULL && root->left == NULL) {
			if(p->right->v == root->v) {
				p->right = NULL;
				free(root);
				return NULL;
			}
			else {
				p->left = NULL;
				free(root);
				return NULL;
			}
			// remove root.
			// respective child node of parent is now NULL
			// free space
		}
		else if (root->right == NULL && root->left != NULL) {
			// Node * p = root->parent;
			if(p->right->v == root->v) {
				p->right = root->left;
			}
			else {
				p->left = root->left;
			}
			root->left->parent = p;
			p = root->left;
			free(root);
			return p;
			// single left subtree exists
			// left subtree parent is now root parent
			// respective child of parent is now left subtree
			// free space
		}
		else if (root->right != NULL && root->left == NULL) {
			// Node * p = root->parent;
			if(p->right->v == root->v) {
				p->right = root->right;
			}
			else {
				p->left = root->right;
			}
			root->right->parent = p;
			p = root->right;
			free(root);
			return p;
			// single right subtree exists
			// right subtree parent is now root parent
			// respective child of parent is now right subtree
			// free space
		}
		else { // full fledged subtree exists
			// root value is now successor
			// call delete on the right subtree for the successor value
			//
			root->v = successor(root->right)->v;
			return delete(root->right,mroot->v);
		}
		// return root
	}
	else if (root->v > val) {
		// call left subtree
		root->left = delete(root->left, val);
	}
	else if (root->v < val) {
		// call right subtree
		root->right = delete(root->right, val);
	}
	return root;
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
		//in_print(bl);
		in_print(bl);
		printf("\n");
		printf("\nDelete: : ");
		scanf("%lld", &datar);
		bl = delete(bl, datar);

		in_print(bl);
		printf("\n");
		// for(Node* i = bl;i!=NULL;) {
		// 	Node * next = successor(i);
		// 	if(next != NULL)
		// 		printf("Successor of %lld is %lld\n", i->v, next->v);
		// 	i = next;
		// }

		// printf("%lld\n", tree_minimum(bl)->v);

		// printf("%lld\n", delete(bl, datar));
	}

	return 0;
}
//
//
// #include<stdio.h>
// #include<stdlib.h>
// typedef long long int ll;
// struct Node
// {
// 	ll val;
// 	struct Node* left;
// 	struct Node* right;
// 	struct Node* parent;
// };
// typedef struct Node node;
// node* insert ( ll n , node *tree)
// {
// 	if(tree==NULL)
// 	{
// 		tree = (node *)malloc(sizeof(node));
// 		tree->val=n;
// 		tree->left=NULL;
// 		tree->right=NULL;
// 		tree->parent=NULL;
//
// 	}
// 	else if(tree->val >= n)
// 	{
// 		if(tree->left == NULL)
// 		{
// 			tree->left= (node *)malloc(sizeof(node));
// 			tree->left->val=n;
// 			tree->left->left=NULL;
// 			tree->left->right=NULL;
// 			tree->left->parent=tree;
// 		}
// 		else
// 		{
// 			tree->left = insert(n,tree->left);
// 		}
// 	}
// 	else
// 	{
// 		if(tree->right == NULL)
// 		{
// 			tree->right = (node *)malloc(sizeof(node));
// 			tree->right->val = n;
// 			tree->right->right=NULL;
// 			tree->right->left=NULL;
// 			tree->right->parent=tree;
//
// 		}
// 		else
// 		{
// 			tree->right=insert(n,tree->right);
// 		}
// 	}
// 	return tree;
// }
// void inorder(node* root)
// {
// 	if ( root == NULL) return;
// 	inorder(root->left);
// 	inorder(root->right);
// 	printf("%lld ",root->val);
//
// }
// node * search(ll n, node* tree)
//
// {
// 	if(tree==NULL)
// 		return NULL;
// 	if(tree->val==n)
// 		return tree;
// 	else if (tree->val>n)
// 		return search(n,tree->left);
// 	else if (tree->val < n )
// 		return search(n,tree->right);
//
// }
// ll getminval(node* tree )
// {
// 	if(tree==NULL)
// 		return -1;//NEVA HAPPN
// 	while(tree->left != NULL)
// 		tree=tree->left;
// 	return tree->val;
// }
// node * delete(node * tree, ll n)
// {
// 	if(tree==NULL)
// 		return NULL;
// 	if(tree->val == n)
// 	{
// 		if (tree->left == NULL)
// 		{
// 			node* new_tree=tree->right;
// 			free(tree);
// 			return new_tree;
// 		}
// 		else if (tree->right == NULL)
// 		{
// 			node* new_tree=tree->left;
// 			free(tree);
// 			return new_tree;
// 		}
// 		else
// 		{
// 			//Find suc and replace and delete
// 			ll suc_val = getminval(tree->right);
// 			tree->val = suc_val ;
// 			tree->right = delete(tree->right,suc_val);
// 		}
// 	}
//
// 	else if (tree-> val > n )
// 	{
// 		tree->left = delete(tree->left,n);
// 	}
// 	else
// 	{
// 		tree->right = delete(tree->right,n);
// 	}
// 	return tree;
//
//
//
// }
// int main()
// {
// 	node* root;
// 	int k;
// 	ll n;
// 	while(1)
// 	{
//
// 		printf("\n1.Insert 2.Search 3.Delete 4.Quit 5.Print\n");
// 		scanf("%d",&k);
// 		if(k==1)
// 		{
// 			scanf("%lld",&n);
// 			root=insert(n,root);
// 		}
// 		else if (k==2)
// 		{
// 			scanf("%lld",&n);
// 			if(search(n,root)==NULL)
// 				printf("false\n");
//
// 			else
// 				printf("true\n");
// 		}
// 		else if (k==4)
// 			break;
// 		else if (k==3)
// 		{
// 			scanf("%lld",&n);
// 			root=delete(root,n);
// 		}
// 		else if (k==4) {
// 			break;
// 		}
// 		else
// 			inorder(root);
//
// 	}
// 	return 0;
// }
