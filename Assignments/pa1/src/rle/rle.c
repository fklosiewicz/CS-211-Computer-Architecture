
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(int argc, char **argv) {

//	char ch = argv[1][0];
	char *compressed;
	compressed = (char *)malloc(((strlen(argv[1]))* 2 + 10) * sizeof(char));
	
	int i;
	for(i = 0; i < strlen(argv[1]); i++) {
	if(isdigit(argv[1][i])) {
		printf("error");
		return EXIT_SUCCESS;
		
		}
	}	
	if((strlen(argv[1])) == 0) {
		printf("\n");
		return EXIT_SUCCESS;
	}

	int length = strlen(argv[1]);
	int start = 1;
	int backtrack = 0;
	
	sprintf(compressed,"%c",argv[1][0]);
	int count = 1;	
	
	while(start < length) {
		if(argv[1][start] == argv[1][backtrack]) {
		count++;
		start++;
		backtrack++;
	//	printf("The count is %d\n",count);
		}
		else {
		sprintf(compressed,"%s%d%c",compressed,count,argv[1][start]);
		count = 1;
		start++;
		backtrack++;
		}
}
	sprintf(compressed, "%s%d", compressed, count);
	if(strlen(compressed) <= strlen(argv[1])) {
		printf("%s", compressed);
	} else {
		printf("%s", argv[1]);
	}

	free(compressed);		

	return EXIT_SUCCESS;

}









