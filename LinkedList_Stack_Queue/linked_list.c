//#include<stdio.h>
//#include<stdlib.h>

#define SINGLE_LINKED_LIST 0


/*
    Single Linked List : ���� ����Ʈ��? �ϳ��� ��尡 Value�� ���� ��带 ��Ÿ���� ���� ������ �ڷᱸ���̴�.
    �� ��, Node�� ���� ��常�� ����Ű�� ������ ���� ���� ����Ʈ��� �Ѵ�.

    ���� ���� ����Ʈ�� �迭�� ��������, �迭�� ũ�Ⱑ �����̰�, ���ټӵ��� ��������,
    ���� ���� ����Ʈ�� ũ�Ⱑ �����̰�, ���ټӵ��� ������.
    ���� �迭�� ���� �� �߰��ϱ� ���ؼ��� ��� ������ �Ѿ�� �迭�� �ٽ� �����ϰ� ���� �� �ű���ۿ� ������,
    ���� ���� ����Ʈ�� ������ ����� ������ �ϱ� ������ ���Ѵ��(���׸�Ʈ ������ �����ִ� ��ŭ) �߰��� �����ϴ�.

    �׷���, ���� �߾Ӱ��� �������� ��, �迭�� �����ʹ� ��� �����̴°�?
    �迭�� ��쿡�� ���� index�� mid��� ���� ��,
    mid+1�� mid�� ���� . . . end-1�� end�� ����
    �� ������, �������� end �����͸� �����ؾ߸� �߰��� �� ������ ��������.

    �׷��� �� ������, ������ ����� Single Linked List�� ��쿡�� ���� ���� �� �� �ִ�.
    �ֳĸ� Node�� value, next_node�� ���� call by reference�� ������,
    �迭ó�� �������� �����͸� �ٲ��� �ʾƵ� �Ǿ ���� ȿ�����̴�.
    
*/
#if SINGLE_LINKED_LIST

typedef struct Node {
    int data;
    struct Node* next_node;
} Node;

/*��� ����*/
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    //printf("%p %p %p", &new_node, &new_node->data, &new_node->next_node);
    new_node->data = data;
    new_node->next_node = NULL;
    return new_node;
}

/*��� ����*/
int is_empty(Node* list) {
    if (list == NULL) {
        return 1;
    }
    return 0;
}

/* ��� �˻� */
Node* search_node(Node* list, int data) {
    if (is_empty(list)) return NULL;

    while (list != NULL) {
        if (list->data == data) return list;
        list = list->next_node;
    }
    return NULL;
}

/*��� �߰�*/
void append_node(Node** head, Node* new_node) {
    if (*head == NULL) *head = new_node;
    else {
        Node* tail = *head;
        while (tail->next_node != NULL) tail = tail->next_node;
        tail->next_node = new_node;
    }
}

/*��� ���*/
void print_list(Node* current) {
    
    if (!is_empty(current)) {
        while (current != NULL) {
            printf("[%p] %d [%p] \n", current, current->data, current->next_node);
            current = current->next_node;
        }
    }
}

/* ��� ���� */
Node* remove_node(Node** head, int data) {
    if (is_empty(head)) return NULL;

    //���� ���ϴ� ��� �˻�
    Node* target = search_node(*head, data);
    if (*head == target) *head = target->next_node;
    else {
        Node* current = *head;
        while (current->next_node != target) {
            current = current->next_node;
        }
        current->next_node = target->next_node;
    }
    target->next_node = NULL;
    return target;
}

/* ����Ʈ ���� */
void delete_list(Node** head) {
    Node* remove = *head;
    Node* next = *head;
    while (remove != NULL) {
        next=next->next_node;
        free(remove);
        remove = next;
    }
    *head = NULL;
}

int main() {
    Node* list = NULL;
    Node* new_node = NULL;
    new_node = create_node(10);
    append_node(&list, new_node);
    new_node = create_node(20);
    append_node(&list, new_node);
    new_node = create_node(30);
    append_node(&list, new_node);
    new_node = create_node(40);
    append_node(&list, new_node);
    new_node = create_node(50);
    append_node(&list, new_node);
    new_node = create_node(60);
    append_node(&list, new_node);

    remove_node(&list, 50);
    remove_node(&list, 40);
    print_list(list);

    delete_list(&list);
    return 0;
}
#endif