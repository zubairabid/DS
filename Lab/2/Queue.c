#include <stdio.h>
#include <stdlib.h>

struct Node {
	long long int data;
	struct Node* next;
};

struct Node* enQueue(struct Node*, long long int);
struct Node* deQueue(struct Node*);
void print(struct Node*);

int main()
{
	struct Node* head = NULL;
	struct Node* tail = NULL;
	long long int temp;

	//head = (struct Node*)malloc(sizeof(struct Node));
	
	for (int i = 0; i < 10; ++i)
	{
		printf("1 for enQueue, 2 for deQueue:\n");;
		scanf("%lld", &temp);
		if(temp == 1) {
			//enQueue
			printf("Val to enQueue:\n");
			scanf("%lld", &temp);

			if(head == NULL) {
				head = (struct Node*)malloc(sizeof(struct Node));
				head->data = temp;
				head->next = NULL;
				tail = head;
			}
			else {
				tail = enQueue(tail, temp);	
			}
			
		}
		else {
			//deQueue
			if(head == NULL) {
				printf("Queue Underflow.\n");
				continue;
			}
			printf("\n*******************\n");
			printf("*******************\n");
			printf("*******************\n");
			printf("*** Returned: %lld ***\n", head->data);
			printf("*******************\n");
			printf("*******************\n");
			printf("*******************\n\n");
			head = deQueue(head);
		}
		print(head);
	}

	return 0;
}

struct Node* enQueue(struct Node* end, long long int dat) {
	struct Node* node = NULL;
	node = (struct Node*)malloc(sizeof(struct Node));
	node->data = dat;
	node->next = NULL;
	end->next = node;
	end = node;

	return end;
}

struct Node* deQueue(struct Node* head) {
	struct Node* temp = head;
	head = head->next;
	free(temp);
	return head;
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
