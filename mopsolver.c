#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Node{
	int x;
	int y;
	int pos;	
	struct Node *north;
	struct Node *south;
	struct Node *east;
	struct Node *west;

}Node;
struct Map{
	int size;
	int n;
	struct Node** nodeList;
};
struct Map* createMap(int size){
	struct Map *map =(struct table*)malloc(sizeof(struct Map));
	map->size=size;
	map->n=0;
	map->nodeList=(struct Node*)malloc(sizeof(struct Node*)*size);
	for(int i=0;i<size;i++){
		map->nodeList[i]=NULL;
	}
	return map;
}
struct Map* increaseSize(struct Map* map,int size){
	map=(struct table*)realloc(map,(sizeof(struct Map)));
	map->nodeList=(struct Node**)realloc(map,sizeof(struct Node*)*size);
	for(int i=map->size; i<size;i++){
		map->nodeList[i]=NULL;
	}	
	map->size=size;
	return map;
}
void insert(struct Map* map,int x,int y){
	int hash=(y*map->n)+x;
	struct Node *newNode=(struct Node*)malloc(sizeof(struct Node));
	newNode->x=x;
	newNode->y=y;
	newNode->pos=
	newNode->north=NULL;
	newNode->south=NULL;
	newNode->east=NULL;
	newNode->west=NULL;
	map->nodeList[hash]=newNode;
}
struct Node* lookup(struct Map* map,int x, int y){
	int hash=(y*map->n)+x;
	struct Node *list=map->nodeList[hash];
	struct Node *temp=list;
	if(temp->x==x&&temp->y==y){
		return temp;
	}
	return NULL;
}
struct Map* readFile(char* INFILE){
	FILE *fp;
	char buf[256];
	char* line=NULL;
	int n=0;
	int x=0;
	int y=0;
	int numNodes=0;
	struct Map *map=createMap(0);
	if(INFILE != NULL){
		fp=fopen(INFILE,"r");
		if(fp==NULL){
			printf("Cannot find file\n");
			exit(EXIT_FAILURE);
		}
		while((line=fgets(buf,256,fp))!=NULL){
			char* token;
			
			if(y==0)
				n=strlen(line)/2;
			while((token=strtok(line," "))!=NULL){
				if(token==0){
					numNodes++;
					map=increaseSize(map,numNodes);
					map->n++;
					insert(map,x,y);
				}
				struct Node *temp=lookup(map,x,y);
				if(temp==NULL){
					printf("1 ");
				}
				else{
					printf("%d,%d ",temp->x,temp->y);
				}
				line=NULL;
				x++;
			}
			x=0;
			y++;

			printf("\n");
		}
	}
	return map;
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
					case'h': 
						printf("-h      Print this helpful message to stdout and exit.\n");
						printf("-d      Pretty print (display) the maze after reading.  (Default: off)\n");
						printf("-s      Print shortest solution steps.        		(Default: off)\n");
						printf("-p 	Print an optimal path.				(Default: off)\n");
						printf("-i INFILE	Read maze from INFILE			(Default: stdin)\n");
						printf("-o OUTFILE	Write all output to OUTFILE		(Default: stdout)\n");
						exit(EXIT_FAILURE);
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
	
	readFile(INFILE);	


	return 0;

}
