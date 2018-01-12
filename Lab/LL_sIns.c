#include <stdio.h>
#include <stdlib.h>

struct LL {
	long long int data;
	struct LL* next;
};

LL* insertBeg(LL*, long long int);
LL* remHead(LL*);

int main()
{
	struct LL* head = NULL;
	struct LL* l = NULL;
	struct LL* p = NULL;
	long long int temp;

	head = (struct LL*)malloc(sizeof(struct LL));
	scanf("%lld", &temp);

	head->data = temp;
	head->next = NULL;

	p = (struct LL*)malloc(sizeof(struct LL));
	p = head;

	for (int i = 0; i < 10; ++i)
	{
		scanf("%lld", &temp);
		l = (struct LL*)malloc(sizeof(struct LL));

		l->data = temp;
		l->next = NULL;

		p->next = l;
		p = l;
	}

	//printing
	printf("Printing\n");
	for (p = head; p != NULL ; p = p->next)
	{
		printf("%lld\n", p->data);
	}
	printf("Done\n");

	
	for (int i = 0; i < 10; ++i)
	{
		scanf("%lld", &temp);
		head = insertBeg(head, temp);
	}

	//printing
	printf("Printing\n");
	for (p = head; p != NULL ; p = p->next)
	{
		printf("%lld\n", p->data);
	}
	printf("Done\n");

	return 0;
}

LL* insertBeg(LL* head, long long int dat) {
	struct LL* node = NULL;
	node = (struct LL*)malloc(sizeof(struct LL));
	node->data = dat;
	node->next = head;
	head = node;

	return head;
}

LL* remHead(LL* head) {
	struct LL* temp = head;
	head = head->next;
	free(temp);
	return head;
}