#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#define MAX_VERTEX 10
#define FALSE 0
#define TRUE 1

// �׷����� ���� ���� ����Ʈ�� ��� ���� ����
typedef struct graphNode {
    int vertex;
    struct graphNode* link;
} graphNode;

typedef struct graphType {
    int n;                            // ���� ����
    graphNode* adjList_H[MAX_VERTEX]; // ������ ���� ���� ����Ʈ�� ��� ��� �迭
    int visited[MAX_VERTEX];          // ������ ���� �湮 ǥ�ø� ���� �迭
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
} //���� >>

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
} // ť >>

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
    
	// �׷��� G9 ����
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
	printf("\n G9�� ���� ����Ʈ ");
	printgraph(G9);

	printf("\n\n///////////////\n\n���� �켱 Ž�� >> ");
	

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
        
		printf("����: ���¾�\n");
		printf("�й�: 2017038096\n");
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
	g -> n = 0; // �׷����� ���� ������ 0���� �ʱ�ȭ
	for(v=0; v<MAX_VERTEX; v++){ 
		g -> visited[v] = FALSE; // �׷����� ������ ���� �迭 vistied�� FALSE�� �ʱ�ȭ
		g -> adjList_H[v] = NULL; // ���� ����Ʈ�� ���� ��� ��� �迭�� NULL�� �ʱ�ȭ
	}
}



int insertvertex(graphType* g, int v)
{
    if(((g -> n)+1)>MAX_VERTEX){ 
        printf("\n �׷��� ������ ������ �ʰ��Ͽ����ϴ�!");
        return 0;
    }
    g -> n++; // �׷����� ���� ���� n�� �ϳ� ����
}

int insertedge(graphType* g, int u, int v) // �׷��� g�� ���� (u, v)�� �����ϴ� ����
{
    graphNode* node;
    if(u >= g -> n || v >= g -> n){ // ���� (u, v)�� �����ϱ� ���� ���� u�� ���� v�� ���� �׷����� �ִ��� Ȯ��
        printf("\n �׷����� ���� �����Դϴ�!");
        return 0;
    }
    node = (graphNode *)malloc(sizeof(graphNode));
    node -> vertex = v;
    node -> link = g -> adjList_H[u]; // ���� ������ ���� ��带 ����Ʈ�� ù ��° ���� ����
    g -> adjList_H[u] = node;
}

void depthFirstSearch(graphType* g, int v) // �׷��� g���� ���� v�� ���� iterative ���� �켱 Ž�� ����
{
  graphNode* w;
  top = NULL;             // ������ top ����
  push(v);                // ���� �켱 Ž���� �����ϴ� ���� v�� ���ÿ� push
  g -> visited[v] = TRUE; // ���� v�� �湮�����Ƿ� �ش� �迭���� TRUE�� ����
  printf(" %c", v + 65);
  

  // ������ ������ �ƴ� ���� ���� �켱 Ž�� �ݺ�
  while(!isEmpty()){
	  v = pop();
	  w = g -> adjList_H[v];

	  while (w){
		  // ���� ���� w�� �湮���� ���� ���
		  if ( !g -> visited[w -> vertex]){
			  if(isEmpty()) push(v); // ���� v�� ���ƿ� ��츦 ���� �ٽ� push�Ͽ� ����
			  push(w -> vertex); //���� ���� w�� ���ÿ� push
			  g -> visited[w -> vertex] = TRUE; // ���� w�� ���� �迭���� TRUE�� ����
			  printf(" %c", w -> vertex + 65); // ���� 0~6�� A~G�� �ٲپ ���
			  v = w -> vertex;
			  w = g -> adjList_H[v];
		  }
          // ���� ���� w�� �̹� �湮�� ���
		  else w = w -> link;
	  } //while (w)
  } // ������ �����̸� ���� �켱 Ž�� ����
}

void breathFirstSearch(graphType* g, int v) // �׷��� g���� ���� v�� ���� �ʺ� �켱 Ž�� ����
{
	graphNode* w;
	LQueueType* Q;           // ť
	Q = createLinkedQueue(); // ť ����
	g -> visited[v] = TRUE; // ���� ���� v�� ���� �迭���� TRUE�� ����
	printf(" %c", v + 65);
	enQueue(Q, v); // ���� ���� v�� ť�� enQueue
    

    //ť�� ������ �ƴ� ���� �ʺ� �켱 Ž�� ����
	while (!isEmpty(Q)){
		
		v = deQueue(Q);
        // ���� ���� w�� �湮���� ���� ���
		for( w = g -> adjList_H[v]; w; w = w -> link) // ���� ������ �ִ� ���� ����
		if(!g -> visited[w -> vertex]) {     // ���� W�� �湮���� ���� ������ ���
			g -> visited[w -> vertex] = TRUE; 
			printf(" %c", w -> vertex + 65); // ���� 0~6�� A~G�� �ٲپ� ���
			enQueue(Q, w -> vertex);
		}
	} // ť�� �����̸� �ʺ� �켱 Ž�� ����

}

void printgraph(graphType* g)
{
	int i;
	graphNode* p;
	for(i=0; i<g -> n; i++){
		printf("\n\t\t���� %c�� ���� ����Ʈ", i + 65);
		p = g -> adjList_H[i];
		while (p){
			printf(" -> %c", p -> vertex + 65);
			p = p -> link;
		}
	}
}