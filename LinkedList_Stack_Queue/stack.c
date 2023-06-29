#include<stdio.h>
#include<stdlib.h>

#define STACK_ARRAY 0
#define STACK_LINKED_LIST 1

/*
	스택 :
	새로운 데이터를 넣고, 기존에 있는 제일 높은 곳에 존재하는 데이터를 삭제할 수 있는
	선형 자료구조이다.

	스택을 구현하기 위해서는 TOP의 포인터를 계속 유지해야 한다.
	왜냐하면 우리는 오로지 스택의 맨 위에 있는 데이터만 접근이 가능하기 때문이다.

	LIFO (Last In First Out) 의 속성을 가진 자료구조이다.
	오로지 마지막에 넣은 자료가 제일 먼저 나오게 된다.

	기본적으로 다섯 개의 함수를 구현한다.

	push(), 스택에 값을 넣는 함수이다.
	pop(), 스택에 있는 값을 빼네는 함수이다.
	top(), 스택 맨 꼭대기에 있는 값을 반환하는 함수이다.
	isEmpty(), 만약 스택이 비어있다면 true를 , 아니면 false를 반환하는 함수이다.
	size(), 스택의 현재 크기를 반환하는 함수이다.


	스택은 컴퓨터 내부 구조에서 다양하게 사용된다.
	중위표기식을 후위표기식으로 바꾸는 스택,
	후위표기식을 계산할 때 사용되는 스택,
	재귀함수에서의 함수실행정보를 담아두는 스택 (어떤 주소로 Jump 해야할지를 담아두는 스택),
	메모리를 관리하는 스택 (예를 들어 c언어의 세그멘테이션 스택),
	undo-redo stack이 존재한다. (우리가 뒤로 가기를 할 때 또는 ctrl + z를 누를 때
	, 정보를 담아두는 스택)

	스택의 구현 방법은 array와 linked list가 존재한다.

	array의 장점: 빠르다, 구현이 쉽다.
	array의 단점: 처음에 지정한 크기가 한정되어 있으므로 
	크기를 초과할 정도의 값을 넣지 못한다. 또한, 고정된 메모리가 할당되어 있어 그 메모리는
	낭비될 수 있다.

	linked list의 장점 : 동적으로 사이즈를 늘릴 수 있어, 메모리 할당이 자유롭다.
	linked list의 단점: 구현이 어려우며, malloc() 함수로 데이터를 동적할당 할 수 있는
	크기가 한정되어 있다.


	두 개를 다 구현해보겠다.

	stack_array는 현재 파일에, 
	stack_linkedlist는 다른 파일에 저장해 두었다.
*/





#if STACK_ARRAY

스택의 구조 [최대 크기를 가르키는 top과, 스택을 담아두는 배열.]
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