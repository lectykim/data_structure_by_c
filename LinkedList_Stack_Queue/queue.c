#define QUEUE 0

#if QUEUE
#define MAX_SIZE 10
#include <stdio.h>
#include<stdlib.h>

/*
	큐(QUEUE) : 
	큐는 FIFO 성질을 가진 선형 데이터 구조이다.
	들어올 수 있는 곳도 하나, 나올 수 있는 곳도 하나이며,
	처음 들어온 요소가 가장 먼저 나가게 된다.

	큐도 배열 구현이랑 링크드리스트 구현이 있다.
	배열 구현은 다음과 같다.
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