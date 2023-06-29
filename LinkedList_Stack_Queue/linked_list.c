//#include<stdio.h>
//#include<stdlib.h>

#define SINGLE_LINKED_LIST 0


/*
    Single Linked List : 연결 리스트란? 하나의 노드가 Value와 다음 노드를 나타내는 노드로 구성된 자료구조이다.
    이 때, Node가 다음 노드만을 가르키기 때문에 단일 연결 리스트라고 한다.

    단일 연결 리스트와 배열의 차이점은, 배열은 크기가 정적이고, 접근속도가 빠르지만,
    단일 연결 리스트는 크기가 동적이고, 접근속도가 느리다.
    또한 배열에 값을 더 추가하기 위해서는 어느 순간이 넘어가면 배열을 다시 선언하고 값을 다 옮길수밖에 없지만,
    단일 연결 리스트는 포인터 기반의 연산을 하기 때문에 무한대로(세그먼트 스택이 남아있는 만큼) 추가가 가능하다.

    그러면, 만약 중앙값을 제거했을 때, 배열과 포인터는 어떻게 움직이는가?
    배열의 경우에는 빠진 index가 mid라고 했을 때,
    mid+1과 mid를 변경 . . . end-1과 end를 변경
    한 다음에, 마지막에 end 데이터를 삭제해야만 중간의 빈 참조가 없어진다.

    그러나 이 과정을, 포인터 기반의 Single Linked List의 경우에는 더욱 쉽게 할 수 있다.
    왜냐면 Node의 value, next_node는 전부 call by reference기 때문에,
    배열처럼 물리적인 데이터를 바꾸지 않아도 되어서 더욱 효율적이다.
    
*/
#if SINGLE_LINKED_LIST

typedef struct Node {
    int data;
    struct Node* next_node;
} Node;

/*노드 생성*/
Node* create_node(int data) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    //printf("%p %p %p", &new_node, &new_node->data, &new_node->next_node);
    new_node->data = data;
    new_node->next_node = NULL;
    return new_node;
}

/*노드 비우기*/
int is_empty(Node* list) {
    if (list == NULL) {
        return 1;
    }
    return 0;
}

/* 노드 검색 */
Node* search_node(Node* list, int data) {
    if (is_empty(list)) return NULL;

    while (list != NULL) {
        if (list->data == data) return list;
        list = list->next_node;
    }
    return NULL;
}

/*노드 추가*/
void append_node(Node** head, Node* new_node) {
    if (*head == NULL) *head = new_node;
    else {
        Node* tail = *head;
        while (tail->next_node != NULL) tail = tail->next_node;
        tail->next_node = new_node;
    }
}

/*노드 출력*/
void print_list(Node* current) {
    
    if (!is_empty(current)) {
        while (current != NULL) {
            printf("[%p] %d [%p] \n", current, current->data, current->next_node);
            current = current->next_node;
        }
    }
}

/* 노드 삭제 */
Node* remove_node(Node** head, int data) {
    if (is_empty(head)) return NULL;

    //삭제 원하는 노드 검색
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

/* 리스트 삭제 */
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