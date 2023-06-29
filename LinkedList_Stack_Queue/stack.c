#include<stdio.h>
#include<stdlib.h>

#define STACK_ARRAY 0
#define STACK_LINKED_LIST 1

/*
	���� :
	���ο� �����͸� �ְ�, ������ �ִ� ���� ���� ���� �����ϴ� �����͸� ������ �� �ִ�
	���� �ڷᱸ���̴�.

	������ �����ϱ� ���ؼ��� TOP�� �����͸� ��� �����ؾ� �Ѵ�.
	�ֳ��ϸ� �츮�� ������ ������ �� ���� �ִ� �����͸� ������ �����ϱ� �����̴�.

	LIFO (Last In First Out) �� �Ӽ��� ���� �ڷᱸ���̴�.
	������ �������� ���� �ڷᰡ ���� ���� ������ �ȴ�.

	�⺻������ �ټ� ���� �Լ��� �����Ѵ�.

	push(), ���ÿ� ���� �ִ� �Լ��̴�.
	pop(), ���ÿ� �ִ� ���� ���״� �Լ��̴�.
	top(), ���� �� ����⿡ �ִ� ���� ��ȯ�ϴ� �Լ��̴�.
	isEmpty(), ���� ������ ����ִٸ� true�� , �ƴϸ� false�� ��ȯ�ϴ� �Լ��̴�.
	size(), ������ ���� ũ�⸦ ��ȯ�ϴ� �Լ��̴�.


	������ ��ǻ�� ���� �������� �پ��ϰ� ���ȴ�.
	����ǥ����� ����ǥ������� �ٲٴ� ����,
	����ǥ����� ����� �� ���Ǵ� ����,
	����Լ������� �Լ����������� ��Ƶδ� ���� (� �ּҷ� Jump �ؾ������� ��Ƶδ� ����),
	�޸𸮸� �����ϴ� ���� (���� ��� c����� ���׸����̼� ����),
	undo-redo stack�� �����Ѵ�. (�츮�� �ڷ� ���⸦ �� �� �Ǵ� ctrl + z�� ���� ��
	, ������ ��Ƶδ� ����)

	������ ���� ����� array�� linked list�� �����Ѵ�.

	array�� ����: ������, ������ ����.
	array�� ����: ó���� ������ ũ�Ⱑ �����Ǿ� �����Ƿ� 
	ũ�⸦ �ʰ��� ������ ���� ���� ���Ѵ�. ����, ������ �޸𸮰� �Ҵ�Ǿ� �־� �� �޸𸮴�
	����� �� �ִ�.

	linked list�� ���� : �������� ����� �ø� �� �־�, �޸� �Ҵ��� �����Ӵ�.
	linked list�� ����: ������ ������, malloc() �Լ��� �����͸� �����Ҵ� �� �� �ִ�
	ũ�Ⱑ �����Ǿ� �ִ�.


	�� ���� �� �����غ��ڴ�.

	stack_array�� ���� ���Ͽ�, 
	stack_linkedlist�� �ٸ� ���Ͽ� ������ �ξ���.
*/





#if STACK_ARRAY

������ ���� [�ִ� ũ�⸦ ����Ű�� top��, ������ ��Ƶδ� �迭.]
#define STACK_MAX_SIZE = 100;

typedef struct Stack {
	int stack[100];
	int top;
} Stack;

void init(Stack* p) {
	p->top = -1;
}

void push(Stack* p, int data) {
	p->top++;
	p->stack[p->top] = data;
}

int pop(Stack* p) {
	int peek = p->stack[p->top];
	p->top--;
	return peek;
}

int peek(Stack* p) {
	return p->stack[p->top];
}

int isEmpty(Stack* p) {
	if (p->top == -1)
		return 1;
	else
		return 0;
}

void print(Stack* p) {
	int index;
	for (index = p->top; index >= 0; index--) {
		printf("[Stack Value] : %d", p->stack[index]);
		printf("\n");
	}
}

int main() {
	Stack* stack = (Stack*)malloc(sizeof(Stack));
	init(stack);
	push(stack, 4);
	push(stack, 8);
	push(stack, 12);
	
}

#endif