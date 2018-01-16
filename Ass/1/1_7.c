#include <stdio.h>
#include <stdlib.h>
#include <string.h>

long long int flow = 1000000007;
char str[2000007];
//long long int stack[10000007];
// long long int head = -1;
struct Node {
	long long int data;
	struct Node* next;
};

struct Node* head = NULL;
void push(long long int);
void pop();

int main()
{
	// struct Node* head = NULL;
	long long int temp, T, i, j;
	long long int dat1, dat2, result;
	char x;
	
	scanf("%lld", &T);

	for (i = 0; i < T; ++i)
	{
		scanf("%s", str);
		//printf("%s\n", str);
		long long int len = strlen(str);

		for (j = 0; j < len; ++j)
		{
			x = str[j];
			// printf("Character: %c\n", x);
			if(x >= '0' && x <= '9') 
			{
				// printf("%lld is a digit. Pushing to stack\n", (long long int)(x-'0'));
				push((long long int)(x-'0'));
			}
			else 
			{
				if(x == '+')
				{
					// printf("Operand found: +\n");
					dat1 = head->data;
					pop();
					dat2 = head->data;
					pop();
					result = dat1 + dat2;
					// printf("Adding %lld and %lld to push %lld to stack\n", dat1, dat2, result);
					push(result%flow);
				}
				if(x == '-')
				{
					// printf("Operand found: -\n");
					dat1 = head->data;
					pop();
					dat2 = head->data;
					pop();
					result = (dat2%flow - dat1%flow + flow)%flow;
					// printf("Subtracting %lld and %lld to push %lld to stack\n", dat2, dat1, result);
					push(result);
				}
				if(x == '*')
				{
					// printf("Operand found: *\n");
					dat1 = head->data;
					pop();
					dat2 = head->data;
					pop();
					result = dat1 * dat2;
					// printf("Multiplying %lld and %lld to push %lld to stack\n", dat1, dat2, result);
					push(result%flow);
				}
				if(x == '/')
				{
					//printf("Operand found: /\n");
					dat1 = head->data;
					pop();
					dat2 = head->data;
					pop();
					result = dat2 / dat1;
					//printf("Dividing %lld and %lld to push %lld to stack\n", dat2, dat1, result);
					push(result%flow);
				}
				
			}
		}

		printf("%lld\n", head->data);
	}
	/*
	for (int i = 0; i < 100; ++i)
	{
		
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
	*/
	return 0;
}


void push(long long int dat) {
	struct Node* node = NULL;
	node = (struct Node*)malloc(sizeof(struct Node));
	node->data = dat;
	node->next = head;
	head = node;
}

void pop() {
	struct Node* temp = head;
	head = head->next;
	free(temp);
}