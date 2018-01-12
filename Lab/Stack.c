#include <stdio.h>
#include <stdlib.h>

struct Node {
	long long int data;
	struct Node* next;
};

struct Node* push(Node*, long long int);
struct Node* pop(Node*);
void print(Node*);

int main()
{
	struct Node* head = NULL;
	long long int temp;

	for (int i = 0; i < 100; ++i)
	{
		/* code */
		printf("1 for push, 2 for pop:\n");
		scanf("%lld", &temp);
		if(temp == 1) {
			//push
			printf("Val to push:\n");
			scanf("%lld", &temp);
			head = push(head, temp);
		}
		else {
			//pop
			if(head == NULL) {
				printf("Stack Underflow.\n");
				continue;
			}
			printf("\n*******************\n");
			printf("*******************\n");
			printf("*******************\n");
			printf("*** Returned: %lld ***\n", head->data);
			printf("*******************\n");
			printf("*******************\n");
			printf("*******************\n\n");
			head = pop(head);
		}
		print(head);

	}

	return 0;
}

void print(Node* head) {
	struct Node* p = NULL;
	printf("------------------------\nPrinting\n\n");
	for (p = head; p != NULL ; p = p->next)
	{
		printf("%lld\n", p->data);
	}
	printf("\nDone\n------------------------\n");
}

struct Node* push(Node* head, long long int dat) {
	struct Node* node = NULL;
	node = (struct Node*)malloc(sizeof(struct Node));
	node->data = dat;
	node->next = head;
	head = node;

	return head;
}

struct Node* pop(Node* head) {
	struct Node* temp = head;
	head = head->next;
	free(temp);
	return head;
}