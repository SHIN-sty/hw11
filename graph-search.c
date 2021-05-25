#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#define MAX_VERTEX 10
#define FALSE 0
#define TRUE 1

// 그래프에 대한 인접 리스트의 노드 구조 정의
typedef struct graphNode {
    int vertex;
    struct graphNode* link;
} graphNode;

typedef struct graphType {
    int n;                            // 정점 개수
    graphNode* adjList_H[MAX_VERTEX]; // 정점에 대한 인접 리스트의 헤드 노드 배열
    int visited[MAX_VERTEX];          // 정점에 대한 방문 표시를 위한 배열
} graphType;

typedef int element;

typedef struct stackNode{
	int data;
	struct stackNode *link;
} stackNode;

stackNode* top;

int isEmpty() {
	if(top == NULL) return 1;
    else return 0;
}

void push(int item)
{
	stackNode* temp = (stackNode *)malloc(sizeof(stackNode));
	temp -> data = item;
	temp -> link =top;
	top=temp;
}

int pop() {
	int item;
	stackNode* temp = top;

	if(isEmpty()) {
		printf("\n\n Stack is empty !\n");
		return 0;
	}
	else{
		item = temp -> data;
		top = temp -> link;
		free(temp);
		return item;
	}
} //스택 >>

typedef struct QNode {
	int data;
	struct QNode *link;
} QNode;

typedef struct {
	QNode *front, *rear;
} LQueueType;

LQueueType * createLinkedQueue() {
	LQueueType *LQ;
	LQ = (LQueueType *)malloc(sizeof(LQueueType));
	LQ -> front = NULL;
	LQ -> rear = NULL;
	return LQ;
}

int isEmpty(LQueueType *LQ){
	if (LQ -> front == NULL){
	printf("\n Linked Queue is empty! \n");
	return 1; 
	}
    else return 0;
}

void enQueue(LQueueType *LQ, int item){
	QNode *newNode = (QNode *)malloc(sizeof(QNode));
	newNode -> data = item;
	newNode -> link = NULL;
	if(LQ -> front == NULL){
		LQ -> front = newNode;
		LQ -> rear = newNode;
	}
	else{
		LQ -> rear -> link = newNode;
		LQ -> rear = newNode;
	}
}

int deQueue(LQueueType *LQ){
	QNode *old = LQ -> front;
	int item;
	if (isEmpty(LQ)) return 0;
	else{
		item = old -> data;
		LQ -> front = LQ -> front ->  link;
		if (LQ -> front == NULL)
		LQ -> rear = NULL;
		free(old);
		return item;
	}
} // 큐 >>

int initializegraph(graphType* g);

int isEmpty();
void push(int item);
int pop();
int isEmpty(LQueueType *LQ);
void enQueue(LQueueType *LQ, int item);
int deQueue(LQueueType *LQ);
int insertvertex(graphType* g, int v);
int insertedge(graphType* g, int u, int v);
void depthFirstSearch(graphType* g, int v);
void breathFirstSearch(graphType* g, int v);

void printgraph(graphType* g);

int main()
{
    char command;
	int u;
	int v;
	int n;
	int i;
	graphNode* node;
    graphType g;
	graphNode* w;
	graphType *G9;
	G9 = (graphType *)malloc(sizeof(graphType));
	initializegraph(G9);
    
	// 그래프 G9 구성
	for(i=0;i<7;i++)
	insertvertex(G9, i);
	insertedge(G9, 0, 2);
	insertedge(G9, 0, 1);
	insertedge(G9, 1, 4);
	insertedge(G9, 1, 3);
	insertedge(G9, 1, 0);
	insertedge(G9, 2, 4);
	insertedge(G9, 2, 0);
	insertedge(G9, 3, 6);
	insertedge(G9, 3, 1);
	insertedge(G9, 4, 6);
	insertedge(G9, 4, 2);
	insertedge(G9, 4, 1);
	insertedge(G9, 5, 6);
	insertedge(G9, 6, 5);
	insertedge(G9, 6, 4);
	insertedge(G9, 6, 3);
	printf("\n G9의 인접 리스트 ");
	printgraph(G9);

	printf("\n\n///////////////\n\n깊이 우선 탐색 >> ");
	

	depthFirstSearch(G9, 0);
    
	getchar();

    do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                       Graph Searches                           \n");
		printf("----------------------------------------------------------------\n");

		printf(" Initialize Graph     = z                                       \n");
		printf(" Insert Vertex        = v      Insert Edge                  = e \n");
		printf(" Depth First Search   = d      Breath First Search          = b \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");
        
		printf("성명: 신태양\n");
		printf("학번: 2017038096\n");
		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializegraph(&g);
			break;
		case 'v': case 'V':
			printf("Your Key = ");
			scanf("%d", &v);
			insertvertex(&g, v);
			break;
		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &v);
			insertedge(&g, u, v);
			break;

		case 'd': case 'D':
			depthFirstSearch(&g, v);
			break;

		case 'b': case 'B':
			breathFirstSearch(&g, v);
			break;

		case 'p': case 'P':
			printgraph(&g);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializegraph(graphType* g)
{
	int v;
	g -> n = 0; // 그래프의 정점 개수를 0으로 초기화
	for(v=0; v<MAX_VERTEX; v++){ 
		g -> visited[v] = FALSE; // 그래프의 정점에 대한 배열 vistied를 FALSE로 초기화
		g -> adjList_H[v] = NULL; // 인접 리스트에 대한 헤드 노드 배열을 NULL로 초기화
	}
}



int insertvertex(graphType* g, int v)
{
    if(((g -> n)+1)>MAX_VERTEX){ 
        printf("\n 그래프 정점의 개수를 초과하였습니다!");
        return 0;
    }
    g -> n++; // 그래프의 정점 개수 n을 하나 증가
}

int insertedge(graphType* g, int u, int v) // 그래프 g에 간선 (u, v)를 삽입하는 연산
{
    graphNode* node;
    if(u >= g -> n || v >= g -> n){ // 간선 (u, v)를 삽입하기 위해 정점 u와 정점 v가 현재 그래프에 있는지 확인
        printf("\n 그래프에 없는 정점입니다!");
        return 0;
    }
    node = (graphNode *)malloc(sizeof(graphNode));
    node -> vertex = v;
    node -> link = g -> adjList_H[u]; // 삽입 간선에 대한 노드를 리스트의 첫 번째 노드로 연결
    g -> adjList_H[u] = node;
}

void depthFirstSearch(graphType* g, int v) // 그래프 g에서 정점 v에 대한 iterative 깊이 우선 탐색 연산
{
  graphNode* w;
  top = NULL;             // 스택의 top 설정
  push(v);                // 깊이 우선 탐색을 시작하는 정점 v를 스택에 push
  g -> visited[v] = TRUE; // 정점 v를 방문했으므로 해당 배열값을 TRUE로 설정
  printf(" %c", v + 65);
  

  // 스택이 공백이 아닌 동안 깊이 우선 탐색 반복
  while(!isEmpty()){
	  v = pop();
	  w = g -> adjList_H[v];

	  while (w){
		  // 현재 정점 w를 방문하지 않은 경우
		  if ( !g -> visited[w -> vertex]){
			  if(isEmpty()) push(v); // 정점 v로 돌아올 경우를 위해 다시 push하여 저장
			  push(w -> vertex); //현재 정점 w를 스택에 push
			  g -> visited[w -> vertex] = TRUE; // 정점 w에 대한 배열값을 TRUE로 설정
			  printf(" %c", w -> vertex + 65); // 정점 0~6을 A~G로 바꾸어서 출력
			  v = w -> vertex;
			  w = g -> adjList_H[v];
		  }
          // 현재 정점 w가 이미 방문된 경우
		  else w = w -> link;
	  } //while (w)
  } // 스택이 공백이면 깊이 우선 탐색 종료
}

void breathFirstSearch(graphType* g, int v) // 그래프 g에서 정점 v에 대한 너비 우선 탐색 연산
{
	graphNode* w;
	LQueueType* Q;           // 큐
	Q = createLinkedQueue(); // 큐 생성
	g -> visited[v] = TRUE; // 시작 정점 v에 대한 배열값을 TRUE로 설정
	printf(" %c", v + 65);
	enQueue(Q, v); // 현재 정점 v를 큐에 enQueue
    

    //큐가 공백이 아닌 동안 너비 우선 탐색 수행
	while (!isEmpty(Q)){
		
		v = deQueue(Q);
        // 현재 정점 w를 방문하지 않은 경우
		for( w = g -> adjList_H[v]; w; w = w -> link) // 인접 정점이 있는 동안 수행
		if(!g -> visited[w -> vertex]) {     // 정점 W가 방문하지 않은 정점인 경우
			g -> visited[w -> vertex] = TRUE; 
			printf(" %c", w -> vertex + 65); // 정점 0~6을 A~G로 바꾸어 출력
			enQueue(Q, w -> vertex);
		}
	} // 큐가 공백이면 너비 우선 탐색 종료

}

void printgraph(graphType* g)
{
	int i;
	graphNode* p;
	for(i=0; i<g -> n; i++){
		printf("\n\t\t정점 %c의 인접 리스트", i + 65);
		p = g -> adjList_H[i];
		while (p){
			printf(" -> %c", p -> vertex + 65);
			p = p -> link;
		}
	}
}