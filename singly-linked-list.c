/*
 * singly linked list
 *
 *  Data Structures
 *  School of Computer Science 
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key; // 해당 노드의 데이터 값을 저장하는 변수
	struct Node* link; // 다음 노드의 주소를 저장하는 포인터 변수
} listNode; // 연결 리스트의 노드 구조체 정의

typedef struct Head {
	struct Node* first; // 연결 리스트의 첫 번째 노드의 주소를 저장하는 포인터 변수
}headNode; // 연결 리스트의 헤드 노드 구조체 정의


/* 함수 리스트 */
headNode* initialize(headNode* h); // 헤드 노드를 초기화하는 함수
int freeList(headNode* h); // 리스트의 모든 노드를 해제하는 함수

int insertFirst(headNode* h, int key); // 첫 번째 노드에 새로운 노드를 삽입하는 함수
int insertNode(headNode* h, int key); // 지정된 키값을 가진 노드 다음에 새로운 노드를 삽입하는 함수
int insertLast(headNode* h, int key); // 리스트의 마지막에 새로운 노드를 삽입하는 함수

int deleteFirst(headNode* h); // 첫 번째 노드를 삭제하는 함수
int deleteNode(headNode* h, int key); // 지정된 키값을 가진 노드를 삭제하는 함수
int deleteLast(headNode* h); // 리스트의 마지막 노드를 삭제하는 함수
int invertList(headNode* h); // 리스트의 노드들을 역순으로 재배치하는 함수

void printList(headNode* h); // 현재 linked list의 상태를 출력하는 함수

// main 함수 시작
int main()
{
    char command; // 입력받은 명령어를 저장하는 변수
    int key; // 입력받은 키 값을 저장하는 변수
    headNode* headnode=NULL; // linked list를 가리키는 head node를 NULL값으로 초기화

    do{
        printf("----------------------------------------------------------------\n");
        printf("                     Singly Linked List                         \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize    = z           Print         = p \n");
        printf(" Insert Node   = i           Delete Node   = d \n");
        printf(" Insert Last   = n           Delete Last   = e\n");
        printf(" Insert First  = f           Delete First  = t\n");
        printf(" Invert List   = r           Quit          = q\n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); // 명령 입력

        switch(command) {
        case 'z': case 'Z':
            headnode = initialize(headnode); // linked list를 초기화하는 함수 호출
            break;
        case 'p': case 'P':
            printList(headnode); // linked list를 출력하는 함수 호출
            break;
        case 'i': case 'I':
            printf("Your Key = ");
            scanf("%d", &key);
            insertNode(headnode, key); // linked list에 노드를 추가하는 함수 호출
            break;
        case 'd': case 'D':
            printf("Your Key = ");
            scanf("%d", &key);
            deleteNode(headnode, key); // linked list에서 노드를 삭제하는 함수 호출
            break;
        case 'n': case 'N':
            printf("Your Key = ");
            scanf("%d", &key);
            insertLast(headnode, key); // linked list의 마지막에 노드를 추가하는 함수 호출
            break;
        case 'e': case 'E':
            deleteLast(headnode); // linked list의 마지막 노드를 삭제하는 함수 호출
            break;
        case 'f': case 'F':
            printf("Your Key = ");
            scanf("%d", &key);
            insertFirst(headnode, key); // linked list의 처음에 노드를 추가하는 함수 호출
            break;
        case 't': case 'T':
            deleteFirst(headnode); // linked list의 처음 노드를 삭제하는 함수 호출
            break;
        case 'r': case 'R':
            invertList(headnode); // linked list를 역순으로 바꾸는 함수 호출
            break;
        case 'q': case 'Q':
            freeList(headnode); // linked list를 동적으로 할당된 메모리를 해제하는 함수 호출
            break;
        default:
            printf("\n       >>>>>   Concentration!!   <<<<<     \n"); // 잘못된 명령어 입력시 경고 메시지 출력
            break;
        }

    }while(command != 'q' && command != 'Q'); // 'q' 또는 'Q'를 입력할 때까지 반복

    return 1; // 프로그램 종료
}


headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴*/
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL;
	return temp;
}

int freeList(headNode* h){
    /* h와 연결된 listnode 메모리 해제
       headNode도 해제되어야 함.
    */
    // h의 첫 번째 노드를 가리키는 포인터 p 선언
    listNode* p = h->first;

    // 이전 노드를 가리키는 포인터 prev 선언 후 NULL로 초기화
    listNode* prev = NULL;

    // p가 NULL이 아닐 때까지 반복
    while(p != NULL) {
        // prev에 p를 저장
        prev = p;
        // p는 다음 노드를 가리키게 함
        p = p->link;
        // prev가 가리키는 노드를 메모리에서 해제
        free(prev);
    }
    // h도 메모리에서 해제
    free(h);
    // 함수 종료
    return 0;
}

/**
 * list 처음에 key에 대한 노드하나를 추가
*/
int insertFirst(headNode* h, int key) {

	// 새로운 노드 생성 후 key 값 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;

	// 새로운 노드를 첫 노드로 추가
	node->link = h->first;
	h->first = node;

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	// listNode 구조체 포인터 node를 동적 할당하고 key값과 link값을 NULL로 초기화
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	// 리스트가 비어있을 경우, 새로운 노드를 첫 번째 노드로 지정하고 함수 종료
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	// 리스트가 비어있지 않을 경우, 리스트를 검색하여 key값보다 큰 값을 가진 노드를 찾아서 새로운 노드를 삽입
	listNode* n = h->first;
	listNode* trail = h->first;

	while(n != NULL) {
		if(n->key >= key) {
			// 새로운 노드를 첫 번째 노드로 지정
			if(n == h->first) {
				h->first = node;
				node->link = n;
			} 
			// 새로운 노드를 노드 n 앞에 삽입
			else {
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;
		n = n->link;
	}

	// 리스트의 모든 노드를 검색했음에도 key값보다 큰 값을 가진 노드가 없을 경우, 새로운 노드를 리스트의 끝에 삽입
	trail->link = node;
	return 0;

}

/* headNode 구조체 포인터 h와 key값을 입력받아 리스트를 검색하여, key값보다 큰 값이 나오는 노드 바로 앞에 노드를 삽입하는 함수 */
int insertLast(headNode* h, int key) {

	// listNode 구조체에 key 값을 저장하고 link는 NULL로 초기화한 후 메모리 동적 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->link = NULL;

	// 리스트가 비어있으면 새로운 노드를 첫 번째 노드로 지정하고 함수 종료
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	// 리스트가 비어있지 않으면 리스트의 끝까지 탐색하고 마지막 노드 뒤에 새로운 노드를 추가
	listNode* n = h->first;
	while(n->link != NULL) {
		n = n->link;
	}
	n->link = node;
	return 0;
}

/**
 * list의 첫번째 노드 삭제
*/
int deleteFirst(headNode* h) {

	// 리스트가 비어있는 경우
	if (h->first == NULL)
	{
		printf("삭제할 노드가 없습니다.\n");
		return -1;
	}

	// 삭제할 노드를 첫번째 노드로 지정하고, 헤드 노드를 두번째 노드로 변경
	listNode* n = h->first;
	h->first = n->link;

	// 첫번째 노드를 삭제하고 메모리를 반환
	free(n);

	return 0;
}

int deleteNode(headNode* h, int key) {

	// 리스트가 비어있으면 0을 반환
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	
	// 리스트의 첫 번째 노드를 가리키는 포인터 n을 초기화하고, n의 앞 노드를 가리키는 포인터 trail을 초기화
	listNode* n = h->first;
	listNode* trail = NULL;


	while(n != NULL) {
		// 현재 노드의 값이 삭제하려는 값과 같다면
		if(n->key == key) {
			
			// 만약 현재 노드가 리스트의 첫 번째 노드라면
			if(n == h->first) {
				// 헤드 노드를 현재 노드의 다음 노드로 바꿔줌
				h->first = n->link;
			} else { 
				// 현재 노드의 이전 노드와 다음 노드를 연결
				trail->link = n->link;
			}
			free(n); // 현재 노드를 메모리에서 해제
			return 0;
		}

		// 삭제하려는 노드를 못찾으면 현재 노드를 이전 노드로 설정하고 다음 노드로 넘어감
		trail = n;
		n = n->link;
	}

	// 삭제하려는 노드를 찾지 못했다면 0 반환
	printf("cannot find the node for key = %d\n", key);
	return 0;
}

/**
 * list의 마지막 노드 삭제
*/
int deleteLast(headNode* h) {

	// 리스트가 비어있으면 0을 반환
	if (h->first == NULL)
	{
		printf("삭제할 노드가 없습니다.\n");
		return 0;
	}

	// 리스트의 첫 번째 노드를 가리키는 포인터 n을 초기화하고, n의 앞 노드를 가리키는 포인터 trail을 초기화
	listNode* n = h->first;
	listNode* trail = NULL;

	// 리스트에 노드가 하나만 있으면 그 노드를 삭제하고 종료
	if(n->link == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	// 리스트의 끝까지 탐색하며 n과 trail의 위치를 이동시킴
	while(n->link != NULL) {
		trail = n;
		n = n->link;
	}

	// n이 마지막 노드를 가리키고 있으므로, trail이 마지막에서 두 번째 노드를 가리키게 하고, n을 삭제
	trail->link = NULL;
	free(n);

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재배치
*/
int invertList(headNode* h) {

	// 리스트가 비어있으면 0을 반환
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}

	// 포인터 변수 n, trail, middle를 선언하고 초기화
	listNode *n = h->first; // 리스트의 첫번째 노드를 가리킴
	listNode *trail = NULL; // middle의 이전 노드를 가리킴
	listNode *middle = NULL; // n의 이전 노드를 가리킴

	// 리스트를 탐색하면서 링크를 역순으로 재배치
	while(n != NULL){
		trail = middle; // trail에 middle을 저장
		middle = n; // middle에 n을 저장
		n = n->link; // n은 다음 노드를 가리킴
		middle->link = trail; // middle의 링크를 trail로 변경
	}

	// 리스트의 첫번째 노드를 middle로 변경
	h->first = middle;

	return 0;

}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	// h가 NULL인 경우 함수 종료
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	// p가 첫 번째 노드를 가리키도록 설정
	p = h->first;

	// p가 NULL이 될 때까지 반복
	while(p != NULL) {
	printf("[ [%d]=%d ] ", i, p->key);
	p = p->link; // p를 다음 노드로 이동
	i++;
}
	printf("  items = %d\n", i); // 출력된 노드의 개수를 출력
}
