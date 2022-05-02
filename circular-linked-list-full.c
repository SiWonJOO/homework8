/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	  printf("[----- [SIWON JOO] [2018038045] -----]");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) { // 노드를 초기화 하는 함수 , 더블포인터로 받은이유는 값을 바꾸기 위해서이다. 

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL) 
		freeList(*h); // 할당된 메모리를 해제

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode)); // 노드를 만들어 메모리를 할당한다.
	(*h)->rlink = *h; // 오른쪽 링크는 자기자신을 가르킨다.
	(*h)->llink = *h; // 왼쪽 링크도 자기자신을 가르킨다.
	(*h)->key = -9999; // 헤드노드의 키값으로 -9999로 대입한다.
	return 1;
}

int freeList(listNode* h){ // 할당된 메모리를 해제하는 함수

	if(h->rlink == h) // 노드가 비어있을때 
	{
		free(h); // 비어있기때문에 바로 메모리 할당을 해제한다.
		return 1; 
	}

	listNode* p = h->rlink; // 헤드노드의 오른쪽링크의 데이터를 가진 p 리스트 노드를 만든다.

	listNode* prev = NULL; // 이전값 노드의 값을 가질 prev 라는 리스트 노드를 만든다.
	while(p != NULL && p != h) { // 노드의 끝까지 반복하면서 메모리 할당을 해제한다.
		prev = p; // prev가 이전노드의 값을 가지게한다.
		p = p->rlink; // 노드를 다음노드로 옮긴다.
		free(prev); // 이전노드의 메모리 할당을 해제한다.
	}
	free(h); 
	return 0;
}



void printList(listNode* h) { // 노드를 출력하는 함수
	int i = 0; // 인덱스 값을 표현하기 위해 선언함
	listNode* p; // 리스트노드 p 를 만든다.

	printf("\n---PRINT\n");

	if(h == NULL) { // 노드가 비어있을경우 오류메세지 출력
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; // 헤드노드의 오른쪽 링크의 값을 p에 대입한다.

	while(p != NULL && p != h) { // 노드의 끝까지 반복한다.
		printf("[ [%d]=%d ] ", i, p->key); // 인덱스값과 키값을 출력한다.
		p = p->rlink; // 노드를 한칸 옮긴다.
		i++; // 인덱스값증가
	}
	printf("  items = %d\n", i); // 노드이 수를 출력한다.


	/* print addresses */
	printf("\n---checking addresses of links\n"); 
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink); // 헤드노드 주소출력

	i = 0;
	p = h->rlink; // 노드를 한칸 옮긴다.
	while(p != NULL && p != h) { // 노드의 끝까지 반복한다.
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink); // 노드들의 주소 출력
		p = p->rlink; // 노드를 한칸 옮긴다.
		i++; // 인덱스값을 증가시킨다.
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	if (h == NULL) return -1; // 노드가 비어있다면(이니셜라이즈 되지 않았다면) 종료한다.

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로운 리스트 노드 node 의 메모리를 할당한다.
	node->key = key; // 새로 만든 노드의 키값에 입력받은 키값을 대입한다.
	node->rlink = NULL; // 노드의 오른쪽 링크를 NULL 로 초기화한다.
	node->llink = NULL; // 노드의 왼쪽 링크를 NULL 로 초기화한다.

	if (h->rlink == h) /* 첫 노드로 삽입 */ // 아직노드의 아무것도 추가하지 않았다면 첫노드로 바로 삽입
	{
		h->rlink = node; // 헤드노드의 오른쪽 링크에 값을 node 로 대입한다.
		h->llink = node; // 헤드노드의 왼쪽 링크에 값을 node 로 대입한다.
		node->rlink = h; // 새로운 노드를 헤드노드로 한다.
		node->llink = h; // 새로운 노드를 헤드노드로 한다.
	} else {  // 만약 노드가 있다면
		h->llink->rlink = node; // 헤드노드의 왼쪽링크의 오른쪽링크가 새로만든 node 의 값을 갖는다.
		node->llink = h->llink; // 새로만든 node 의 왼쪽링크가 헤도노드의 왼쪽링크 값을 갖는다.
		h->llink = node; // 헤드노드의 왼쪽링크가 새로운 node 의 값을 갖는다.
		node->rlink = h; // 새로운 노드의 오른쪽링크가 헤드노드값을 갖는다.
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) { 

	if (h->llink == h || h == NULL) // 노드가 비어있다면 오류메세지 출력한다.
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* nodetoremove = h->llink; // 노드를 지우기위한 리스트노드를 선언하고 그 노드는 헤드노드의 왼쪽링크 값을 갖는다.

	/* link 정리 */
	nodetoremove->llink->rlink = h; // nodetoremove 의 왼쪽링크의 오른쪽링크는 헤드노드의 값을 갖는다.
	h->llink = nodetoremove->llink; // 헤드노드의 왼쪽링크는  nodetoremove 의 왼쪽링크 값을 갖는다.

	free(nodetoremove); // 메모리 할당을 해제한다.

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) { 

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로 추가할 노드를 만들어 메모리를 할당한다.
	node->key = key; // 입력받은 키값을 만든 노드의 키에 대입한다.
	node->rlink = NULL; // 새로 만든 노드의 오른쪽 링크를 NULL 값으로 초기화한다.
	node->llink = NULL; // 새로 만든 노드의 왼쪽 링크를 NULL 값으로 초기화한다.


	node->rlink = h->rlink; // 새로 만든 노드의 오른쪽 링크가 헤드노드의 오른쪽 링크 값을 갖는다.
 	h->rlink->llink = node; // 헤드노드의 오른쪽 링크의 왼쪽 링크가 NODE의 값을 갖는다.
	node->llink = h; // NODE 의 왼쪽링크의 값은 헤드노드의 값을 갖는다. 
	h->rlink = node; // 헤드노드의 오른쪽 링크는 노드의 값을 갖는다.
	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	if (h == NULL || h->rlink == h) // 노드가 비어있따면 오류메세지 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* nodetoremove = h->rlink; // 노드를 삭제하기 위한 nodetoremove 노드를 선언하고 헤도노드의 오른쪽 링크 값을 갖는다.

	/* link 정리 */
	nodetoremove->rlink->llink = h; // nodetoremove 노드의 오른쪽링크의 왼쪽링크가 헤드노드 값을 가진다.
	h->rlink = nodetoremove->rlink; // 헤드노드의 오른쪽 링크는 nodetoremove의 오른쪾 링크의 값을 가진다.

	free(nodetoremove); // nodetoremove 의 메모리 할당을 해제한다.

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {


	if(h->rlink == h || h == NULL) { // 노드가 비어있다면 오류메세지 출력
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->rlink; // 헤드노드의 오른쪽 링크의 값은 갖는 노드 n 을 선언한다.
	listNode *trail = h; // 이전값을 가질 trail 노드를 선언하고 trail은 헤드노드의 값을 가진다.
	listNode *middle = h; // 중간 값을 가질 middle 노드를 선언하고 middle 은 헤드노드의 값을 가진다.

	/* 최종 바뀔 링크 유지 */
	h->llink = h->rlink; 

	while(n != NULL && n != h){ //노드의 끝에 도달할떄까지 반복한다.
		trail = middle; // traill 노드의 middle 노드 값을 저장한다.
		middle = n; // middle 노드의 n 노드 값을 저장한다.
		n = n->rlink; // 노드를 한칸 움직인다.
		//노드를 역순으로 배치
		middle->rlink = trail; // middle 노드의 오른쪽 링크는 trail 값을 가진다.
		middle->llink = n; // middle 노드의 왼쪽 링크는 n 값을 가진다
	}

	h->rlink = middle; // 헤드노드의 오른쪽 링크는 middle 값을 가진다.

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	if(h == NULL) return -1; // 헤드노드가 비었다면 종료한다.

	listNode* node = (listNode*)malloc(sizeof(listNode)); // 새로 삽입할 리스트노드 구조체 node 를 선언하고 메모리를 할당해준다.
	node->key = key; // node 의 키값에 입력받은 키 값을 대입한다.
	node->llink = node->rlink = NULL; // node 의 왼쪽링크와 오른쪽 링크를 NULL 값으로 초기화한다.

	if (h->rlink == h) // 노드의 오른쪽 링크가 헤드노드를 가르킨다면 즉 추가된 노드가 하나도없을때
	{
		insertFirst(h, key); // 제일 앞에 삽입하는 함수 호출
		return 1;
	}

	listNode* n = h->rlink; // 헤드노드의 오른쪽 링크의 값을 갖는 리스트 노드 n 을 선언한다.

	/* key를 기준으로 삽입할 위치를 찾는다 */
	while(n != NULL && n != h) { // 노드의 끝까지 반복한다.
		if(n->key >= key) { 
			/* 첫 노드 앞쪽에 삽입해야할 경우 인지 검사 */
			if(n == h->rlink) { 
				insertFirst(h, key);
			} else { /* 중간이거나 마지막인 경우 */
				node->rlink = n; // 새로운 노드의 오른쪽 링크의 값은 n의 값을 갖는다.
				node->llink = n->llink; // node 의 왼쪽링크는 n노드의 왼쪽링크의 값을 갖는다.
				n->llink->rlink = node; // n 노드의 왼쪽링크의 오른쪽 링크는 node 값을 가즌다.
				n->llink = node; // n노드의 왼쪽링크는 node 의 값을 갖는다.
			}
			return 0;
		}

		n = n->rlink; // 노드를 한칸 옮긴다.
	}

	/* 마지막 노드까지 찾지 못한 경우, 마지막에 삽입 */
	insertLast(h, key); // 입력받은 키값이 제일 크다면 마지막에 삽입하는 함수 호출
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	if (h->rlink == h || h == NULL) // 노드가 비어있다면 오류메세지 출력
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->rlink; // 헤드노드의 오른쪽 링크의 값을 갖는 리스트노드 구조체 n 을 선언한다.

	while(n != NULL && n != h) { // 노드의 끝까지 반복
		if(n->key == key) {
			if(n == h->rlink) { /* 첫 노드째 노드 인경우 */
				deleteFirst(h); // 첫번째 노드를 삭제하는 함수 호출
			} else if (n->rlink == h){ /* 마지막 노드인 경우 */
				deleteLast(h); // 마지막 노드를 삭제하는 함수 호출
			} else { /* 중간인 경우 */
				n->llink->rlink = n->rlink; // 노드 n 의 왼쪽링크의 오른쪽 링크는 n의 오른쪽 링크 값을 갖는다.
				n->rlink->llink = n->llink; // 노드 n 의 오른쪽 링크의 왼쪽링크는 n의 왼쪽 링크 값을 갖는다.
				free(n); // 삭제한 노드 n 의 메모리 할당을 해제해준다.
			}
			return 0;
		}

		n = n->rlink; // 노드를 한칸 옮긴다.
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


