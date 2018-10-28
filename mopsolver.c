#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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

	return 0;

}
