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

Node* left_rotate(Node* x) {
  Node* y = x->right;
  x->right = y->left;
  y->left = x;
  x->height = 1 + max(get_height(x->left), get_height(x->right));
  y->height = 1 + max(get_height(y->left), get_height(y->right));
  return y;
}

Node* right_rotate(Node* x) {
  Node* y = x->left;
  x->left = y->right;
  y->right = x;
  x->height = 1 + max(get_height(x->left), get_height(x->right));
  y->height = 1 + max(get_height(y->left), get_height(y->right));
  return y;
}
