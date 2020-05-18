//Sean Droke
//Monday April 15, 2019
//CIS 3207
//Project 4

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "filesys.h"

void options();
void functional();

int main(void){
    char inputString[25];
    
    setup();

    printf("\n Your File System has Initialized, welcome to drive C\n\n");
    
    while(1){
        options();
        printf("> ");
        scanf("%25s", inputString);
        functional(inputString);
    }
}

void options(){
    printf("CHOOSE FROM THE FOLLOWING OPTIONS\n");
    printf("*CREATE*\n");
    printf("*DELETE*\n");
    printf("*READ*\n");
    printf("*WRITE*\n");
    printf("*CD*\n");
    printf("*MKDIR*\n");
    printf("*INFO*\n");
    printf("*LIST*\n");
    printf("*EXIT*\n");
}

void functional(char str[]){
    char fileName[12];

	if (strcmp(str, "create") == 0){ 
		printf("create selected\n");
		printf("File Name (Up to 12 characters with extension): ");
		scanf("%12s", fileName);
		createFile(fileName, 0);		
	}
	else if (strcmp(str, "delete") == 0){				
		printf("File Name: ");
		scanf("%12s", fileName);
		deleteFile(fileName);
	}
	else if (strcmp(str, "read") == 0){					
		printf("File Name: ");
		scanf("%12s", fileName);
		openFileRead(fileName);
	}
	else if (strcmp(str, "write") == 0){
		char *dataBlock = calloc(65536, sizeof(char));	
		printf("File Name: ");
		scanf("%12s", fileName);
		printf("Begin...\n");
		if(read(STDIN_FILENO, dataBlock, 65536) < 0){
		}
		openFileWrite(fileName, dataBlock);
		free(dataBlock);
	}
	else if (strcmp(str, "cd") == 0){
		printf("Directory Name: ");
		scanf("%12s", fileName);
		changeDirectory(fileName);
	}
    else if (strcmp(str, "mkdir") == 0){  				
		printf("Directory Name (Up to 12 characters with extension): ");
		scanf("%12s", fileName);
		createFile(fileName, 1); 						
	}
	else if (strcmp(str, "info") == 0){  				
		printf("File Name: ");
		scanf("%12s", fileName);
		fileInfo(fileName);
	}
	else if (strcmp(str, "list") == 0){					
		directoryList();	
	}
	else if (strcmp(str, "exit") == 0){					
		leave();	
	}
	else {
		printf("ERROR INVALID\n");
	}
}