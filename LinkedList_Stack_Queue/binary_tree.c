#define BINARY_TREE_LINKEDLIST

#include<stdio.h>
#include<stdlib.h>

/*
	���� Ʈ����?
	���� Ʈ����. ������ ��尡 �ִ� �� ���� �ڽ� ��带 ������ Ʈ�� �ڷᱸ����.
	���� �ڽ��� left node, ������ �ڽ��� right node��� �Ѵ�.

	��ǻ�ÿ�����, ���� Ʈ���� ���� �ٸ� �� ���� ������� ���ȴ�.
	ù°, � �� �Ǵ� �� ���� ������ ���̺� ����� ��忡 �������ϴ� �����̴�.
	�� ����� ���� Ʈ���� ���� Ž�� Ʈ���� ���� �� ������ ���Ǹ�,
	ȿ������ �˻��� ������ ���� ���ȴ�. 
	��°, ���� �б� ������ �̿��� ������ ǥ��, �̷��� ��� �ٸ� ����� �Ʒ��� ����,
	�Ǵ� �����ʿ� ��带 Ư���ϰ� ��ġ�Ѵ�. �̰��� ������ �Ϻ��̴�.

	������ �Լ��� ������ ����.
	
	insert : Ʈ���� ���� �����Ѵ�.
	delete : Ʈ���� ���� �����Ѵ�.
	print : �ش� ����� left,right,root���� ����Ѵ�.
	preorder_print: ���� ��ȸ
	inorder_print: ���� ��ȸ
	postorder_print: ���� ��ȸ

*/
typedef struct node {
	int data;
	struct node* left;
	struct node* right;
}node;

node* root;

node* insert(node* p, int data) {
	//p�� null�� ���,
	if (p == NULL) {
		//��Ʈ���� �ؼ� ��ü �ʱ�ȭ
		p = (node*)malloc(sizeof(node));
		p->data = data;
		p->left = NULL;
		p->right = NULL;
		return p;
	}
	else {
		//��Ʈ���� ���� ��� left node Ž��
		if (p->data > data) {
				p->left = insert(p->left, data);
		}
		//��Ʈ���� Ŭ ��� right node Ž��
		else {
				p->right = insert(p->right, data);
		}
		return p;
	}
}

node* fMin(node* p)
{
	node* min = p;
	//�� ���� ��忡 ������ �� ���� �ݺ�
	while (min->left != NULL) {
		min = min->left;
	}
	return min;
}

node* delete(node* p,int data) {

	node* tmp_root = NULL;

	//��尡 null�̸� return null
	if (p == NULL)
		return NULL;
	//��Ʈ�� �����ͺ��� ������ ���� Ž��
	else if (p->data > data) {
		//p->left�� ������, 
		/*
			A
		B		C
		�� ��쿡��,
		A�� ����� ���, B�� �ڸ��� A�� �Űܾ��ϱ� ����,
		�׸��� �� ������ left�� ��ȭ�� ��� ��尡 ���¸� �����ؾ� ��.
		�׸��� NULL�� �������� ��쿡�� �� ������ ��ȿ.
		*/
		p->left = delete(p->left, data);
	}
	else if (p->data < data) {
		//right�� ���� ������ ����.
		p->right = delete(p->right, data);
	}
	else {
		//�� ���� ��尡 ������ �� ��Ʈ�� data���,
		if (p->left != NULL && p->right != NULL) {
			tmp_root = fMin(p->right);
			p->data = tmp_root->data;
			p->right = delete(p->right, tmp_root->data);
		}
		else {
			//�ڽ��� ���ʹۿ� ���� ���� ���� ��Ʈ�� 
			//�θ��� left�� right�� ����ִ´�.
			//�̴� 
			/*
				A
			B		
			��,
				B
					
			�� ���·� ����� �Ͱ� ����.
			�׸��� �޸𸮸� �������ش�.
			*/
			tmp_root = (p->left == NULL) ? p->right : p->left;
			free(p);
			return tmp_root;
		}
	}
	return p;
		
	
}
//���� ��ȸ
void preorder_print(node* p) {
	if (p == NULL)
		return;

	printf(" %d ", p->data);
	preorder_print(p->left);
	preorder_print(p->right);
}

//���� ��ȸ
void inorder_print(node* p) {
	if (p == NULL)
		return;
	
	inorder_print(p->left);
	printf(" %d ", p->data);
	inorder_print(p->right);
}

//���� ��ȸ
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