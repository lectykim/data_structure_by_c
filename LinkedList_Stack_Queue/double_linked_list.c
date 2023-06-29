#include<stdio.h>
#include<stdlib.h>

#define DOUBLE_LINKED_LIST 0;


/*
	���� ���� ����Ʈ : �� ��带 ����Ű�� �����Ͱ� �߰��Ǿ�, ����� Ž���� �����ϴ�.

*/
//��� ����
#if DOUBLE_LINKED_LIST

typedef struct Node{
	int data;
	Node* prev_node;
	Node* next_node;
} Node;

//��� ����
Node* create_node(int data) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = data;
	new_node->prev_node = NULL;
	new_node->next_node = NULL;
	return new_node;
}

//��� �߰�
void append_node(Node** head, Node* new_node) {
	if (*head == NULL) *head = new_node;
	else {
		Node* tail = *head;
		while (tail->next_node != NULL) tail->next_node;
		//���� ���� ����Ʈ�� ��쿡�� �� �ʿ� ����� �ּҸ� �޾��ش�.
		tail->next_node = new_node;
		new_node->prev_node = tail;
	}
}

//��� ����
Node* saerch_node(Node* current, int data) {
	if (current == NULL) return NULL;
	//data�� ���� �� ���� ��� Ž��
	while (current != NULL) {
		if (current->data == data) return current;
		current=current->next_node;
	}
	return NULL;
}

//��� ����
Node* remove_node(Node** head, int data) {
	Node* target = search_node(*head, data);
	//ã�� ���� �����ϰ�
	if (target != NULL) {
		//�� ���� HEAD���
		if (*head == target) {
			*head = target->next_node;
			//HEAD�� NEXT_NODE�� �Ǹ�, NEXT_NODE�� PREV_NODE�� NULL�� �ȴ�.
			if (*head != NULL) {
				(*head)->prev_node = NULL;
				//���� ����� �޸𸮸� �����Ѵ�.
				//free((*head)->prev_node);
			}
		}
		else {
			//HEAD�� �ƴ� ���̶��? ���� ����Ʈ�� ���� ����Ʈ�� �ּҸ� ���� ����Ʈ�� ���� �ּҷ� �ٲ۴�.
			if (target->next_node != NULL) target->next_node->prev_node = target->prev_node;
			//�׸��� ���� ����Ʈ�� ���� ����Ʈ�� �ּҸ� Ÿ�� ����Ʈ�� ���� ����Ʈ�� �ּҷ� �ٲ۴�.
			target->prev_node->next_node = target->next_node;
		}
		target->prev_node = NULL;
		target->next_node = NULL;
	}
	return target;
}

//��� �޸� ����
void destroy_node(Node* node) {
	free(node);
}

//����Ʈ ���
void print_list(Node* current) {
	if (current == NULL) printf("empty list \n");
	else {
		while (current != NULL) {
			printf("[%p] %p %d %p \n", current, current->prev_node, current->data, current->next_node);
			current = current->next_node;
		}
	}
}

//����Ʈ ����
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