#define STACK_LINKED_LIST 0

#if STACK_LINKED_LIST
#include<stdio.h>
#include<stdlib.h>

//test commit 2
typedef struct list {
	int data;
	struct list* head;
	struct list* tail;
}list;

typedef struct {
	struct list* top;
} stack;

void put(stack *p, int data);
int peek(stack *p);
int pop(stack *p);
int is_empty(stack *p);
void print(stack *p);

int main() {
	stack* s = (stack*)malloc(sizeof(stack));
	s->top = NULL;
	put(s, 10);
	printf("%d", peek(s));
	put(s, 20);
	printf("%d", peek(s));
	printf("%d", pop(s));
	printf("%d", peek(s));
	put(s, 30);
	put(s, 40);
	put(s, 60);
	put(s, 30);
	put(s, 20);
	put(s, 10);
	print(s);
}



void put(stack* p, int data) {
	if (p->top == NULL) {
		p->top = (list*)malloc(sizeof(list));
		p->top->data = data;
	}
	else {
		list* temp = (list*)malloc(sizeof(list));
		p->top->head = temp;
		temp->tail = p->top;
		temp->data = data;
		p->top = temp;
	}
}

int peek(stack* p) {
	return p->top->data;
}

int pop(stack* p) {
	int data = p->top->data;

	//p->top�� �ּҰ� ��ġ�� �̸� �����ϱ�
	list* temp_list_2 = p->top;
	if (p->top->tail != NULL) {
		//tail �����͸� �̸� �����ص�
		list* temp_list = p->top->tail;

		//top�� ����
		free(temp_list_2);

		//�� ĭ ���� �����͸� �ٽ� �����ϱ�.
		p->top = temp_list;
	}
	else {
		free(temp_list_2);
	}
	return data;
}


int is_empty(stack* p) {
	if (p->top == NULL)
		return 1;
	else
		return 0;
}

void print(stack* p) {
	if (p->top == NULL) {
		printf("[Stack is empty] \n");
		return;
	}
	else {
		int index = 0;
		list* temp = p->top;
		while (temp->tail != NULL) {
			printf("[%d] ��°�� �׿��ִ� ������ �� : %d \n", index++, temp->data);
			temp = temp->tail;
		}
	}
}

#endif