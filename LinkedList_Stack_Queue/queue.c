#define QUEUE 0

#if QUEUE
#define MAX_SIZE 10
#include <stdio.h>
#include<stdlib.h>

/*
	ť(QUEUE) : 
	ť�� FIFO ������ ���� ���� ������ �����̴�.
	���� �� �ִ� ���� �ϳ�, ���� �� �ִ� ���� �ϳ��̸�,
	ó�� ���� ��Ұ� ���� ���� ������ �ȴ�.

	ť�� �迭 �����̶� ��ũ�帮��Ʈ ������ �ִ�.
	�迭 ������ ������ ����.
*/

typedef struct {
	int front, rear, size;
	int* arr;
}Queue;

void init(Queue* q) {

}

void en_queue(Queue* q, int data) {
	//if(q->size==0){
	//	q->arr[q->rear] = data;
	//	q->front++;
	//	q->size++;
	//}
	
		int idx = q->front;
		for (idx; idx > q->rear; idx--) {
			q->arr[idx] = q->arr[idx - 1];
		}
		q->arr[q->rear] = data;
		q->front++;
		q->size++;
	
	
}

int de_queue(Queue* q) {
	if (q->size == 0) {
		return 0;
	}
	else {
		q->size--;
		q->front--;
		int temp = q->arr[q->front];
		return temp;
	}
}

int peek(Queue* q) {
	if (q->size == 0) {
		return 0;
	}
	return q->arr[q->front-1];
}

void main() {
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->front = 1;
	q->rear = 1;
	q->size = 0;
	q->arr = (int*)malloc(sizeof(int) * MAX_SIZE);

	en_queue(q, 10);
	en_queue(q, 20);
	printf("%d", de_queue(q));
	printf("%d", de_queue(q));
	en_queue(q, 30);
	en_queue(q, 40);
	printf("%d", peek(q));
	printf("%d", peek(q));
	printf("%d", de_queue(q));
	printf("%d", de_queue(q));
}

#endif