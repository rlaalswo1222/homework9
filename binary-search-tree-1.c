/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

int initializeBST(Node** h);

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command;
	int key;
	Node* head = NULL;
	Node* ptr = NULL;	/* temp */
	printf("[----- [�����] [2021041070] -----]\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head); // Ʈ�� ����
			break;
		case 'q': case 'Q':
			freeBST(head); // �����Ҵ� ����
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); // ��� �߰�
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key); //��� ����
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key); // ��� �˻�
			if(ptr != NULL) // �˻��� ��尡 �ִٸ�
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); // ���� ��ȸ
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); // ���� ��ȸ
			break;
		case 't': case 'T':
			postorderTraversal(head->left); // ���� ��ȸ
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); // ����� ���� �Ҵ�
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; 
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left); // ���ʼ���Ʈ�� ���� ��ȸ
		printf(" [%d] ", ptr->key); // ���� ��� ���
		inorderTraversal(ptr->right); // �� �� �����ʼ���Ʈ�� ��ȸ 
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key); // ���� ��带 ���� ��� ��
		preorderTraversal(ptr->left); // ���� ����Ʈ�� ��ȸ
		preorderTraversal(ptr->right); // �� �� ������ ����Ʈ�� ��ȸ
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left); //���� ����Ʈ�� ���� ��ȸ 
		postorderTraversal(ptr->right); // �� �� ������ ����Ʈ�� ��ȸ
		printf(" [%d] ", ptr->key); // ���� ��带 ���
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // ������ ��� ����
	newNode->key = key; // ����� �����Ͱ��� �Է°����� ����
	newNode->left = NULL; 
	newNode->right = NULL;

	if (head->left == NULL) { // ��Ʈ ��尡 ���� ��
		head->left = newNode; // ������ ��带 ��Ʈ ���� ����
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; // ������� Ȱ�� 

	Node* parentNode = NULL; // �θ��� = �������� �������� Ȱ��
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // ���� �Է°��� ���� ��庸�� ũ�ٸ�
			ptr = ptr->right; // ������ �ڽĳ��� �̵�
		else // �ƴ϶��
			ptr = ptr->left; // ���� �ڽĳ��� �̵�
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) // ���� �θ����� ���� �Է°����� ũ�ٸ�
		parentNode->left = newNode; // �θ����� ���� �ڽĳ�带 ������ ���� ����
	else
		parentNode->right = newNode; // �θ����� ������ �ڽĳ�带 ������ ���� ����
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) { // ����尡 ���ٸ�
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { // ��Ʈ��尡 ���ٸ�
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left; // ���� ���� Ȱ��


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head; //�θ��� = �������� �������� Ȱ��

	while(ptr != NULL) {

		if(ptr->key == key) { //�Է°��� ���� ����� ���� ���ٸ�
			if(ptr->left == NULL && ptr->right == NULL) { // �ڽĳ�尡 ���ٸ�

				/* root node case */
				if(parentNode == head) //�θ��尡 ������ ���ٸ�
					head->left = NULL; //������� ���� �ڽĳ�带 ����

				/* left node case or right case*/
				if(parentNode->left == ptr) // �θ����� �����ڽĳ�尡 ������� ���ٸ�
					parentNode->left = NULL; // �θ����� ���� �ڽĳ�带 ���� 
				else
					parentNode->right = NULL; // �θ����� ������ �ڽĳ�带 ���� 

				free(ptr); // ������ ���� 
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) // �������� ������ �Է°��� �� ũ�ٸ�
			ptr = ptr->right; // ������ �ڽĳ��� �̵� 
		else
			ptr = ptr->left; // ���� �ڽĳ��� �̵�


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) // ��尡 ����ٸ�
		return NULL;

	if(ptr->key < key) // ���� �������� ������ �Է°��� �� ũ�ٸ�
		ptr = searchRecursive(ptr->right, key); // �������� ������ �ڽĳ��� �˻������ �ű�
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key); // �������� ���� �ڽĳ��� �˻������ �ű�

	/* if ptr->key == key */
	return ptr; // ã�Ҵٸ� �Է°� ��ȯ 

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key) // ���� �Է°��� �������� ���� ���ٸ�
			return ptr; // �ش� ����� �ּҰ��� ��ȯ

		if(ptr->key < key) ptr = ptr->right; // ���� �Է°��� �� ũ�ٸ� ������ �ڽĳ��� �̵�
		else
			ptr = ptr->left; // �۴ٸ� ���� �ڽĳ��� �̵�
	}

	return NULL; // ã�����ߴٸ� NULL ��ȯ
}

void freeNode(Node* ptr) 
{
	if(ptr) {
		freeNode(ptr->left); //����� ����,������ �ڽĳ�� ����
		freeNode(ptr->right);
		free(ptr); //�ڽĳ�� ���� �� �ش��� ����
	}
}

int freeBST(Node* head)
{

	if(head->left == head) //��Ʈ��尡 ���ٸ�
	{
		free(head); // ����� ����
		return 1;
	}

	Node* p = head->left;

	freeNode(p); //��� ��� ���� ���� 

	free(head); //����� ����
	return 1;
}





