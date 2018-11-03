#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KRED "\x1B[31m"
#define RESET "\x1B[0m"
typedef struct Node{
	int x;
	int y;
	int val;
	int rank;
	int shortPath;	
	struct Node* north;		
	struct Node* south;		
	struct Node* east;		
	struct Node* west;		
}Node;
typedef struct Queue{
	struct Node** items;
	int size;
	int back;
	int front;
}Queue;

struct Node createNode(int value,int row,int col){
	Node aNode;
	aNode.val=value;
	aNode.x=col;
	aNode.y=row;
	aNode.rank=-1;
	aNode.shortPath=0;
	aNode.north=NULL;
	aNode.south=NULL;
	aNode.east=NULL;
	aNode.west=NULL;
	return aNode;
}
struct Queue* createQueue(int size){
	struct Queue* q=malloc(sizeof(struct Queue)*10*size);
	q->items=malloc(sizeof(struct Node)*10*size);
	q->size=size;
	q->front=0;
	q->back=0;
	return q;
}
void enqueue(Queue *q,Node *n){
	q->items[q->back]=n;
	q->back++;
}
Node *dequeue(Queue *q){
	Node *n = q->items[q->front];
	q->front++;
	return n;
}
int queueSize(Queue *q){
	return(q->back-q->front);
}
void printQueue(Queue *q){
	printf("Queue[%d]:",queueSize(q));
	
	for(int i=0;i<q->size;i++){
		Node *curr=q->items[i];
		if(curr!=NULL)
			printf("[%d,%d] ",curr->x,curr->y);
	}
	printf("\n");

}
int* sizeOfMaze(char INFILE[]){
	FILE *fp=fopen(INFILE,"r");
	int* xy=malloc(sizeof(int)*2);
	int row=0;
	int col=0;
	int line=1;
	char *buf=NULL;
	size_t len=0;
	while(getline(&buf,&len,fp)>0){
		for(unsigned int i=0;i<strlen(buf);i++){
			if(buf[i]>47 && buf[i]<58 && line==1){
				col++;
			}	
		}
		row++;
		line++;
	}
	xy[0]=row;
	xy[1]=col;
	return xy;
}
void initMatrix(char INFILE[],int x,int y,Node matrix[y][x]){
	FILE *fp;
	char buf[256];
	char* line=NULL;
	int row=0;
	int col=0;

	if(INFILE != NULL){
		fp=fopen(INFILE,"r");
		if(fp==NULL){
			printf("Cannot find file\n");
			exit(EXIT_FAILURE);
		}
		while((line=fgets(buf,256,fp))!=NULL){
			char* token;
			while((token=strtok(line," "))!=NULL){	
					matrix[row][col]=createNode(atoi(token),row,col);	
					//printf("%d ",matrix[row][col].val);
					col++;
					
				line=NULL;
			}
			row++;
			col=0;
			//printf("\n");
		}
	}
}
void printHelp(){
	printf("-h      Print this helpful message to stdout and exit.\n");
	printf("-d      Pretty print (display) the maze after reading.  (Default: off)\n");
	printf("-s      Print shortest solution steps.        		(Default: off)\n");
	printf("-p 	Print an optimal path.				(Default: off)\n");
	printf("-i INFILE	Read maze from INFILE			(Default: stdin)\n");
	printf("-o OUTFILE	Write all output to OUTFILE		(Default: stdout)\n");
	exit(EXIT_FAILURE);
}
void setNeighbors(int x,int y,Node matrix[y][x]){
	for(int i=0;i<y;i++){
		for(int j=0;j<x;j++){
			if(matrix[i][j].val==0){
				if(i!=0&&matrix[i-1][j].val!=1){
					matrix[i][j].north=&matrix[i-1][j];
				}if(i!=y-1&&matrix[i+1][j].val!=1){
					matrix[i][j].south=&matrix[i+1][j];
				}if(j!=0&&matrix[i][j-1].val!=1){
					matrix[i][j].west=&matrix[i][j-1];
				}if(j!=x-1&&matrix[i][j+1].val!= 1){
					matrix[i][j].east=&matrix[i][j+1];
				}
			}
		}
	}
}

int BFS(int x,int y,Node matrix[y][x]){
	if(matrix[0][0].val==0&&matrix[y-1][x-1].val==0){
		Node *curr=&matrix[0][0];	
		//if(curr!=NULL)	
		//	printPointerNode(curr);
		//printPointerNode(curr->south);	
		Queue *q=createQueue(x*y);
		enqueue(q,curr);
		curr->rank=1;
		curr->shortPath=1;
		while(queueSize(q)!=0){
			if(curr->north!=NULL &&curr->north->val==0 && curr->north->rank==-1){
				enqueue(q,curr->north);
				curr->north->rank=curr->rank+1;
			}
			if(curr->south!=NULL &&curr->south->val==0 && curr->south->rank==-1){
				enqueue(q,curr->south);
				curr->south->rank=curr->rank+1;
			}
			if(curr->east!=NULL &&curr->east->val==0 && curr->east->rank==-1){
				enqueue(q,curr->east);
				curr->east->rank=curr->rank+1;
			}
			if(curr->west!=NULL &&curr->west->val==0 && curr->west->rank==-1){
				enqueue(q,curr->west);
				curr->west->rank=curr->rank+1;
			}
			Node *dq=dequeue(q);
			//printf("Rank: %d Row: %d Col: %d\n",dq->rank,dq->y,dq->x);
			curr = q->items[q->front];
		}
		return(matrix[y-1][x-1].rank);
	}
	else
		return -1;
}
void BackTrack(int x,int y,Node matrix[y][x]){
	int start=matrix[y-1][x-1].rank;
	Node *cur=&matrix[y-1][x-1];
	for(int i=start;i>0;i--){
		if(cur->north!=NULL&&cur->north->rank==i){
			cur->shortPath=1;
			cur=cur->north;
		}if(cur->south!=NULL&&cur->south->rank==i){
			cur->shortPath=1;
			cur=cur->south;
		}if(cur->east!=NULL&&cur->east->rank==i){
			cur->shortPath=1;
			cur=cur->east;
		}if(cur->west!=NULL&&cur->west->rank==i){
			cur->shortPath=1;
			cur=cur->west;
		}
	}


}
void printPointerNode(Node *node){
	printf("Node[%d,%d] ", node->x,node->y);
	printf("val:%d ",node->val);
	if(node->north!=NULL)
		printf("north:[%d,%d] ",node->north->x,node->north->y);
	if(node->south!=NULL)
		printf("south:[%d,%d] ",node->south->x,node->south->y);
	if(node->east!=NULL)
		printf("east:[%d,%d] ",node->east->x,node->east->y);
	if(node->west!=NULL)
		printf("west:[%d,%d]",node->west->x,node->west->y);
	printf("\n");
}
void printNode(Node node){
	printf("Node[%d,%d] ", node.x,node.y);
	printf("val:%d ",node.val);
	if(node.north!=NULL)
		printf("north:[%d,%d] ",node.north->x,node.north->y);
	if(node.south!=NULL)
		printf("south:[%d,%d] ",node.south->x,node.south->y);
	if(node.east!=NULL)
		printf("east:[%d,%d] ",node.east->x,node.east->y);
	if(node.west!=NULL)
		printf("west:[%d,%d]",node.west->x,node.west->y);
	printf("\n");
}
void printNeighbors(int x,int y,Node matrix[y][x]){
	for(int i=0;i<y;i++){
		for(int j=0;j<x;j++){
			printNode(matrix[i][j]);			
		}
	}
}
void prettyPrint(int x,int y,Node matrix[y][x]){
	for(int i=0;i<2*x+3;i++){
		if(i==0 || i==x*2+2)
			printf("|");
		else
			printf("-");
	}
	printf("\n");
	for(int j=0;j<y;j++){
		if(j!=0)
			printf("|");
		else
			printf(" ");
		for(int k=0;k<x;k++){
			if(matrix[j][k].shortPath==1){
				printf(KRED" +"RESET);
			}
			else if(matrix[j][k].val==0)
				printf(" .");
			else
				printf(" #");
		}
		if(j!=y-1)
			printf(" |\n");
		else
			printf("  \n");
	}
	for(int l=0;l<2*x+3;l++){
		if(l==0 || l==x*2+2)
			printf("|");
		else
			printf("-");
	}
	printf("\n");
}

int main(int argc,char* argv[]){
	int pretty=0;
	int shortest=0;
	int path=0;
	char* INFILE = NULL;
	char* OUTFILE =NULL;

	for(int i=1;i< argc;i++){
		if(argv[i][1]=='i'&& argv[i+1]!=NULL && argv[i+1][0]!='-'){
			INFILE=argv[i+1];
			i++;
		}
		else if(argv[i][1]=='o' && argv[i+1]!=NULL && argv[i+1][0]!='-'){
			OUTFILE=argv[i+1];
			i++;
		}
		else if(argv[i][0]=='-'){
			for(int j =1;j<(int)strlen(argv[i]);j++){
				switch(argv[i][j]){
					case'h': printHelp();break; 
					case'd': pretty=1; break;
					case's': shortest=1; break;
					case'p': path=1; break;
					default:
						 printf("Usage: mopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\n");
						 exit(EXIT_FAILURE);
				}
			} 
		}
		else {
			printf("Usage: mopsolver [-hdsp] [-i INFILE] [-o OUTFILE]\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("%d %d %d %s %s\n",pretty,shortest,path,INFILE,OUTFILE);
	int* xy=sizeOfMaze(INFILE);
	int y=xy[0];
	int x=xy[1];
	
	//printf("size:%d,%d \n",x,y);
	Node matrix[y][x];
	initMatrix(INFILE,x,y,matrix);	
	if(pretty){
		prettyPrint(x,y,matrix);	
	}	

	setNeighbors(x,y,matrix);

	//printNeighbors(x,y,matrix);	
	int numSteps=BFS(x,y,matrix);
	if(numSteps!=-1){
		printf("Solution in %d steps.\n",numSteps);	
		BackTrack(x,y,matrix);
	}
	else
		printf("No solution.\n");
	prettyPrint(x,y,matrix);
	return 0;

}
