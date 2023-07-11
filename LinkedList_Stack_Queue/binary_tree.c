#define BINARY_TREE_LINKEDLIST

#include<stdio.h>
#include<stdlib.h>

/*
	이진 트리란?
	이진 트리란. 각각의 노드가 최대 두 개의 자식 노드를 가지는 트리 자료구조다.
	왼쪽 자식을 left node, 오른쪽 자식을 right node라고 한다.

	컴퓨팅에서는, 이진 트리는 아주 다른 두 가지 방식으로 사용된다.
	첫째, 어떤 값 또는 각 노드와 연관된 레이블에 기반한 노드에 엑세스하는 수단이다.
	이 방식의 이진 트리는 이진 탐색 트리와 이진 힙 구현에 사용되며,
	효율적인 검색과 정렬을 위해 사용된다. 
	둘째, 연관 분기 구조를 이용한 데이터 표현, 이러한 경우 다른 노드의 아래와 왼쪽,
	또는 오른쪽에 노드를 특정하게 배치한다. 이것은 정보의 일부이다.

	구현할 함수는 다음과 같다.
	
	insert : 트리에 값을 삽입한다.
	delete : 트리의 값을 삭제한다.
	print : 해당 노드의 left,right,root값을 출력한다.
	preorder_print: 전위 순회
	inorder_print: 중위 순회
	postorder_print: 후위 순회

*/
typedef struct node {
	int data;
	struct node* left;
	struct node* right;
}node;

node* root;

node* insert(node* p, int data) {
	//p가 null일 경우,
	if (p == NULL) {
		//루트부터 해서 전체 초기화
		p = (node*)malloc(sizeof(node));
		p->data = data;
		p->left = NULL;
		p->right = NULL;
		return p;
	}
	else {
		//루트보다 작을 경우 left node 탐색
		if (p->data > data) {
				p->left = insert(p->left, data);
		}
		//루트보다 클 경우 right node 탐색
		else {
				p->right = insert(p->right, data);
		}
		return p;
	}
}

node* fMin(node* p)
{
	node* min = p;
	//맨 왼쪽 노드에 도착할 때 까지 반복
	while (min->left != NULL) {
		min = min->left;
	}
	return min;
}

node* delete(node* p,int data) {

	node* tmp_root = NULL;

	//노드가 null이면 return null
	if (p == NULL)
		return NULL;
	//루트의 데이터보다 작으면 왼쪽 탐색
	else if (p->data > data) {
		//p->left인 이유는, 
		/*
			A
		B		C
		의 경우에서,
		A가 사라질 경우, B의 자리를 A로 옮겨야하기 때문,
		그리고 그 정보는 left가 변화한 모든 노드가 상태를 공유해야 함.
		그리고 NULL이 도착했을 경우에도 이 내용은 유효.
		*/
		p->left = delete(p->left, data);
	}
	else if (p->data < data) {
		//right도 위의 이유와 같음.
		p->right = delete(p->right, data);
	}
	else {
		//양 쪽의 노드가 존재할 때 루트가 data라면,
		if (p->left != NULL && p->right != NULL) {
			tmp_root = fMin(p->right);
			p->data = tmp_root->data;
			p->right = delete(p->right, tmp_root->data);
		}
		else {
			//자식이 왼쪽밖에 없는 경우는 왼쪽 루트를 
			//부모의 left나 right에 집어넣는다.
			//이는 
			/*
				A
			B		
			를,
				B
					
			의 형태로 만드는 것과 같다.
			그리고 메모리를 해제해준다.
			*/
			tmp_root = (p->left == NULL) ? p->right : p->left;
			free(p);
			return tmp_root;
		}
	}
	return p;
		
	
}
//전위 순회
void preorder_print(node* p) {
	if (p == NULL)
		return;

	printf(" %d ", p->data);
	preorder_print(p->left);
	preorder_print(p->right);
}

//중위 순회
void inorder_print(node* p) {
	if (p == NULL)
		return;
	
	inorder_print(p->left);
	printf(" %d ", p->data);
	inorder_print(p->right);
}

//후위 순회
void postorder_print(node* p) {
	if (p == NULL)
		return;
	postorder_print(p->left);
	postorder_print(p->right);
	printf(" %d ", p->data);
}

void main() {
	root = insert(root, 5);
	root = insert(root, 1);
	root = insert(root, 9);

	printf("preorder : ");
	preorder_print(root);
	printf("\n");
	printf("inorder : ");
	inorder_print(root);
	printf("\n");
	printf("postorder : ");
	postorder_print(root);
	printf("\n\n");


	printf("preorder : ");
	preorder_print(root);
	printf("\n");

	printf("delete : 9\n");
	root = delete(root, 9);

	preorder_print(root);
	printf("\n");

	root = insert(root, 9);

	printf("delete : 1\n");
	root = delete(root, 1);

	preorder_print(root);
	printf("\n");

	root = insert(root, 1);

	printf("delete : 5\n");
	root = delete(root, 5);

	preorder_print(root);
	printf("\n");
}