#define QUEUE_LN 0

#if QUEUE_LN
#include <stdio.h>
#include <stdlib.h>


typedef struct linkedlist {
	int data;
	struct linkedlist* head;
	struct linkedlist* tail;
}linkedlist;

typedef struct {
	struct linkedlist* front;
	struct linkedlist* peek;
}queue;

void en_queue(queue* q, int data) {
	if (q->front == NULL) {
		linkedlist* source= (linkedlist*)malloc(sizeof(linkedlist));
		source->data = data;
		q->peek = source;
		q->front = source;
	}
	else {
		linkedlist* source = (linkedlist*)malloc(sizeof(linkedlist));
		source->data = data;
		source->head = q->front;
		q->front->tail = source;
		q->front = source;
	}

}

int de_queue(queue* q) {
	int data = 0;
	if (q->peek == NULL) {
		printf("[[[Queue is Empty]]]");
		return 0;
	}
	else {
		data = q->peek->data;
		linkedlist* temp = q->peek;
		q->peek = temp->tail;
		free(temp);
		return data;
	}
}

int is_empty(queue* q) {
	if (q->peek == NULL)
		return 1;
	else
		return 0;
}

int peek(queue* q) {
	if (q->peek == NULL) {
		printf("[[[Queue is Empty]]]");
		return 0;
	}
	else {
		int data = q->peek->data;
		return data;
	}
}

void print(queue* q) {
	if (q->peek == NULL) {
		printf("[[[Queue is Empty]]]");
	}
	else {
		int index = 0;
		linkedlist* temp = q->peek;
		while (temp->tail != NULL) {
			printf("[[[%d]]]번째로 쌓여있는 큐의 값 : %d \n", index++, temp->data);
			temp = temp->tail;
		}
	}
}

void main() {
	queue* q = (queue*)malloc(sizeof(queue));
	q->front = NULL;
	q->peek = NULL;
	en_queue(q,10);
	en_queue(q, 20);
	en_queue(q, 30);
	en_queue(q, 40);
	en_queue(q, 50);
	en_queue(q, 60);
	//printf("%d", peek(q));
	printf("%d", de_queue(q));
	printf("%d", de_queue(q));
	printf("%d", peek(q));
	printf("%d", de_queue(q));
	print(q);
}
#endif