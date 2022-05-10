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
	printf("[----- [김민재] [2021041070] -----]\n");
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
			initializeBST(&head); // 트리 생성
			break;
		case 'q': case 'Q':
			freeBST(head); // 동적할당 해제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); // 노드 추가
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key); //노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key); // 노드 검색
			if(ptr != NULL) // 검색된 노드가 있다면
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
			inorderTraversal(head->left); // 중위 순회
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); // 전위 순회
			break;
		case 't': case 'T':
			postorderTraversal(head->left); // 후위 순회
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
	*h = (Node*)malloc(sizeof(Node)); // 헤드노드 동적 할당
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; 
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr)
{
	if(ptr) {
		inorderTraversal(ptr->left); // 왼쪽서브트리 먼저 순회
		printf(" [%d] ", ptr->key); // 현재 노드 출력
		inorderTraversal(ptr->right); // 그 후 오른쪽서브트리 순회 
	}
}

void preorderTraversal(Node* ptr)
{
	if(ptr) {
		printf(" [%d] ", ptr->key); // 현재 노드를 먼저 출력 후
		preorderTraversal(ptr->left); // 왼쪽 서브트리 순회
		preorderTraversal(ptr->right); // 그 후 오른쪽 서브트리 순회
	}
}

void postorderTraversal(Node* ptr)
{
	if(ptr) {
		postorderTraversal(ptr->left); //왼쪽 서브트리 먼저 순회 
		postorderTraversal(ptr->right); // 그 후 오른쪽 서브트리 순회
		printf(" [%d] ", ptr->key); // 현재 노드를 출력
	}
}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node)); // 삽입할 노드 생성
	newNode->key = key; // 노드의 데이터값을 입력값으로 지정
	newNode->left = NULL; 
	newNode->right = NULL;

	if (head->left == NULL) { // 루트 노드가 없을 시
		head->left = newNode; // 삽입할 노드를 루트 노드로 지정
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; // 현재노드로 활용 

	Node* parentNode = NULL; // 부모노드 = 현재노드의 이전노드로 활용
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
		if(ptr->key < key) // 만약 입력값이 현재 노드보다 크다면
			ptr = ptr->right; // 오른쪽 자식노드로 이동
		else // 아니라면
			ptr = ptr->left; // 왼쪽 자식노드로 이동
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) // 만약 부모노드의 값이 입력값보다 크다면
		parentNode->left = newNode; // 부모노드의 왼쪽 자식노드를 삽입할 노드로 지정
	else
		parentNode->right = newNode; // 부모노드의 오른쪽 자식노드를 삽입할 노드로 지정
	return 1;
}

int deleteLeafNode(Node* head, int key)
{
	if (head == NULL) { // 헤드노드가 없다면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { // 루트노드가 없다면
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left; // 현재 노드로 활용


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head; //부모노드 = 현재노드의 이전노드로 활용

	while(ptr != NULL) {

		if(ptr->key == key) { //입력값과 현재 노드의 값이 같다면
			if(ptr->left == NULL && ptr->right == NULL) { // 자식노드가 없다면

				/* root node case */
				if(parentNode == head) //부모노드가 헤드노드와 같다면
					head->left = NULL; //헤드노드의 왼쪽 자식노드를 제거

				/* left node case or right case*/
				if(parentNode->left == ptr) // 부모노드의 왼쪽자식노드가 현재노드와 같다면
					parentNode->left = NULL; // 부모노드의 왼쪽 자식노드를 제거 
				else
					parentNode->right = NULL; // 부모노드의 오른쪽 자식노드를 제거 

				free(ptr); // 현재노드 해제 
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
		if(ptr->key < key) // 현재노드의 값보다 입력값이 더 크다면
			ptr = ptr->right; // 오른쪽 자식노드로 이동 
		else
			ptr = ptr->left; // 왼쪽 자식노드로 이동


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(ptr == NULL) // 노드가 비었다면
		return NULL;

	if(ptr->key < key) // 만약 현재노드의 값보다 입력값이 더 크다면
		ptr = searchRecursive(ptr->right, key); // 현재노드의 오른쪽 자식노드로 검색대상을 옮김
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key); // 현재노드의 왼쪽 자식노드로 검색대상을 옮김

	/* if ptr->key == key */
	return ptr; // 찾았다면 입력값 반환 

}
Node* searchIterative(Node* head, int key)
{
	/* root node */
	Node* ptr = head->left;

	while(ptr != NULL)
	{
		if(ptr->key == key) // 만약 입력값과 현재노드의 값이 같다면
			return ptr; // 해당 노드의 주소값을 반환

		if(ptr->key < key) ptr = ptr->right; // 만약 입력값이 더 크다면 오른쪽 자식노드로 이동
		else
			ptr = ptr->left; // 작다면 왼쪽 자식노드로 이동
	}

	return NULL; // 찾지못했다면 NULL 반환
}

void freeNode(Node* ptr) 
{
	if(ptr) {
		freeNode(ptr->left); //노드의 왼쪽,오른쪽 자식노드 해제
		freeNode(ptr->right);
		free(ptr); //자식노드 해제 후 해당노드 해제
	}
}

int freeBST(Node* head)
{

	if(head->left == head) //루트노드가 없다면
	{
		free(head); // 헤드노드 해제
		return 1;
	}

	Node* p = head->left;

	freeNode(p); //헤드 노드 제외 해제 

	free(head); //헤드노드 해제
	return 1;
}





