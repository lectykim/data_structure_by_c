#include<stdio.h>
#include<stdlib.h>

#define DOUBLE_LINKED_LIST 0;


/*
	이중 연결 리스트 : 앞 노드를 가리키는 포인터가 추가되어, 양방향 탐색이 가능하다.

*/
//노드 정의
#if DOUBLE_LINKED_LIST

typedef struct Node{
	int data;
	Node* prev_node;
	Node* next_node;
} Node;

//노드 생성
Node* create_node(int data) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = data;
	new_node->prev_node = NULL;
	new_node->next_node = NULL;
	return new_node;
}

//노드 추가
void append_node(Node** head, Node* new_node) {
	if (*head == NULL) *head = new_node;
	else {
		Node* tail = *head;
		while (tail->next_node != NULL) tail->next_node;
		//이중 연결 리스트의 경우에는 양 쪽에 노드의 주소를 달아준다.
		tail->next_node = new_node;
		new_node->prev_node = tail;
	}
}

//노드 선택
Node* saerch_node(Node* current, int data) {
	if (current == NULL) return NULL;
	//data랑 같을 때 까지 계속 탐색
	while (current != NULL) {
		if (current->data == data) return current;
		current=current->next_node;
	}
	return NULL;
}

//노드 삭제
Node* remove_node(Node** head, int data) {
	Node* target = search_node(*head, data);
	//찾는 값이 존재하고
	if (target != NULL) {
		//그 값이 HEAD라면
		if (*head == target) {
			*head = target->next_node;
			//HEAD는 NEXT_NODE가 되며, NEXT_NODE의 PREV_NODE는 NULL이 된다.
			if (*head != NULL) {
				(*head)->prev_node = NULL;
				//이전 노드의 메모리를 해제한다.
				//free((*head)->prev_node);
			}
		}
		else {
			//HEAD가 아닌 값이라면? 다음 리스트의 이전 리스트의 주소를 현재 리스트의 이전 주소로 바꾼다.
			if (target->next_node != NULL) target->next_node->prev_node = target->prev_node;
			//그리고 이전 리스트의 다음 리스트의 주소를 타겟 리스트의 다음 리스트의 주소로 바꾼다.
			target->prev_node->next_node = target->next_node;
		}
		target->prev_node = NULL;
		target->next_node = NULL;
	}
	return target;
}

//노드 메모리 해제
void destroy_node(Node* node) {
	free(node);
}

//리스트 출력
void print_list(Node* current) {
	if (current == NULL) printf("empty list \n");
	else {
		while (current != NULL) {
			printf("[%p] %p %d %p \n", current, current->prev_node, current->data, current->next_node);
			current = current->next_node;
		}
	}
}

//리스트 삭제
void destroy_list(Node* current) {
	Node* remove = current;
	while (remove != NULL) {
		current = current->next_node;
		free(remove);
		remove = current;
	}
}

int main() {
	Node* head = NULL;
	Node* new_node = NULL;

	new_node = create_node(10);
	append_node(&head, new_node);
	print_list(head);
}

#endif