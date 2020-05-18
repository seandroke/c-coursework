//Sean Droke
//Monday April 15, 2019
//CIS 3207
//Project 4

/*
PROGRAM DESCRIPTION: The following is an implementation of a command line file system.
					 The file system is to be run by compiling this file and depends
					 on a 9MB size file by the name of C also included in this submission.
					 In addition, the file system relies on the following dependencies.
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>
#include <unistd.h> 	

/*
CONSTANT INITIALIZATION:

	DRIVELETTER -- Drive letter of the file system
	BLOCKSIZE -- Size of each data block
	TOTALBLOCKS -- Total number of data blocks on the system
	MAXFILESIZE -- Maximum supported file size of files saved to the file system
	FATOFFSET -- Offset of the location of the FAT on the drive
	INFOSECOFFSET -- Offset of the information section of each file
	DATAOFFSET -- Offset of the data section of each file
*/

#define DRIVELETTER "C"		
#define BLOCKSIZE 512
#define TOTALBLOCKS 1098   	
#define MAXFILESIZE 256   		
#define FATOFFSET 0  	
#define INFOSECOFFSET 1 	
#define DATAOFFSET 3

/*
GLOBAL VARIABLE INITIALIZATION:

	*fp -- File pointer used throughout the program for accssessing file system
	temp(#) -- All temporary placeholders used throughout funcitons
	*empty(##) -- Blank placeholders of varrying sizes
	currentDirectory -- Numerical value of current directory
*/

FILE *fp; 
char temp2[3];
char temp4[5];
char temp6[6]; 
char *empty32[32] = { NULL };
char *empty64[64] = { NULL };
long currentDirectory = 0;

/*
STRUCT INITIALIZATION:

	fat -- File Allocation Table structure
		open -- Bit to represent whether the space is available
		fileName -- Name of the FAT entry
		infoSecRef -- Info section pointer
		dataRef -- Data section pointer
		nextRef -- Linker to the next element

	infosec -- Info Section Structure for File
		fileName -- Name of the file
		extension -- Extension of the file
		creation(DateElement) -- Date and time the file was created
		modification(DateElement) -- Date and time the fiel was modified
		fileSize -- Total size of the file

	data -- Empty initialized data block
		blank -- Blank data for memory management purposes
	
	line -- Empty initialized line element
		blank -- Empty line for memory management purposes
*/

struct fat{		
	char open[1];		
	char fileName[12]; 
	char infoSecRef[6];	
	char dataRef[6]; 	
	char nextRef[6];	
};

struct infoSec{		
	char fileName[12];  	
	char extension[3]; 			
	char creationYear[4];	
	char creationMonth[2]; 	
	char creationDay[2]; 	
	char creationHour[2]; 	
	char creationMinute[2]; 	
	char creationSecond[2]; 	
	char modificationYear[4];	
	char modificationMonth[2]; 	
	char modificationDay[2]; 	
	char modificationHour[2]; 	
	char modificationMinute[2]; 	
	char modificationSecond[2]; 	
	char fileSize[6];		
};

struct data{		
	char blank[512];
};

struct line{		
	char blank[16];
};

/*
FUNCTION INITIALIZATION:
*/

FILE setup();
void bootSectorInit();
char *findFreeSpace(int selection);
int findFile(char *fileName);
char *getDateTime(int choice);

void createFile(char *fileName, int alarm);
void deleteFile(char *fileName);
void openFileRead(char *fileName);
void openFileWrite(char *fileName, char *toWrite);
void changeDirectory(char *fileName);
void fileInfo(char *fileName);
void directoryList();
void leave();


void options();
void functional();

/*
--MAIN FUNCTION--

DESCRIPTION:
	- Main is the driver of the program, used to interact with the user such that selections can be made
	- Begins by running setup() to initialize the file system
	- Then, until exit of the system, the prompt will spawn revelaing options to the user
	- Then scan in user input and process requests 25 characters at a time

PARAMETERS:
	None -- Void Function

RETURN:
	None -- Main Function
*/

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

/*
--OPTIONS FUNCTION--

DESCRIPTION:
	- Options is responsible for printing the possible options to the user
	- Each possible option is printed on a new line

PARAMETERS:
	None -- Void Function

RETURN:
	None -- Void Function
*/

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

/*
--FUNCTIONAL FUNCTION--

DESCRIPTION:
	- Functional is responsible for processing the user interface requests
	- Each possible case coordinates to a respective function
	- Void function returns to the main program loop at completion 

PARAMETERS:
	str -- String passed into the function via the user interface

RETURN:
	None -- Void Function
*/

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

/*
--SETUP FILE--

DESCRIPTION:
	- Setup is responsible for opening the drive to be used as a file system and calling on a funciton to initialize the boot sector routine

PARAMETERS:
	None -- File creation

RETURN:
	*fp -- File pointer to the new opened file system 
*/

FILE setup(){
	fp = fopen(DRIVELETTER, "r+");
	bootSectorInit();
	return *fp;
}

/*
--BOOT SECTOR INITIALIZATION FUNCTION--

DESCRIPTION:
	- Initialization function is used to prepare the file system for manipulation
	- Begins by creating the root of the FAT
	- Root is assigned a 1 indiating that it is not an open component of the FAT
	- Temporary variables used to create pointer to info and data sections based on respective offset
	- No linker exists as this is the only element in the FAT
	- Seek to the next section of the file system
	- Set the current directory
	- current is known as a .
	- Seek to the next section and initialize the root of the infosec
	- Set the initial properties as defined below
	- Write them to the info section of the root directory

PARAMETERS:
	None -- Void Function

RETURN:
	None -- Void Function
*/

void bootSectorInit() {
	int i = 0;
	fseek(fp, 0, SEEK_SET);		
	
    struct fat FATroot = {""}; 
	strcpy(FATroot.open, "1");
	strcpy(FATroot.fileName, "/");
	sprintf(temp6, "%u", BLOCKSIZE * INFOSECOFFSET / 16 + 1); 
	strcpy(FATroot.infoSecRef,temp6);
	sprintf(temp6, "%u", BLOCKSIZE * DATAOFFSET / 16 + 1);	
	strcpy(FATroot.dataRef, temp6);
	strcpy(FATroot.nextRef, "-1");								
	fwrite(&FATroot, sizeof(struct fat), 1, fp);

	fseek(fp, BLOCKSIZE * DATAOFFSET, SEEK_SET);
	currentDirectory = DATAOFFSET * BLOCKSIZE;
	fputs(".", fp);										

	i = fseek(fp, BLOCKSIZE * INFOSECOFFSET, SEEK_SET); 

	struct infoSec root = {""}; 
	strcpy(root.fileName, "/");
	strcpy(root.extension, "DIR");
	strcpy(root.creationYear, getDateTime(1));
	strcpy(root.creationMonth, getDateTime(2));
	strcpy(root.creationDay, getDateTime(3));	
	strcpy(root.creationHour, getDateTime(4));
	strcpy(root.creationMinute, getDateTime(5));
	strcpy(root.creationSecond, getDateTime(6));
	strcpy(root.modificationYear, getDateTime(1));
	strcpy(root.modificationMonth, getDateTime(2));
	strcpy(root.modificationDay, getDateTime(3));	
	strcpy(root.modificationHour, getDateTime(4));
	strcpy(root.modificationMinute, getDateTime(5));
	strcpy(root.modificationSecond, getDateTime(6));
	strcpy(root.fileSize, "000000");

	fwrite(&root, sizeof(struct infoSec), 1, fp);
	
}

/*
--FIND FREE SPACE FUNCTION--

DESCRIPTION:
	- Find Free Space function is used to find space for FAT, Info, and Data section entries.
	- Selection parameter determines what free space we are looking for
	- In each case we seek open blocks or spaces and return references to these locales
	- If selection is invalid we throw an exceptoin

PARAMETERS:
	Selection -- Selection to determine what space to look for

RETURN:
	temp6 -- Temporary location of the free space
	-1 -- If an error occurs
*/

char *findFreeSpace(int selection){
    if(selection == 1){
        char open[1];
        fseek(fp, 0, SEEK_SET);	
        for(int i = 0; i < (INFOSECOFFSET * BLOCKSIZE); i+= 32){
            fseek(fp, i, SEEK_SET);
            fread(open, 1, 1, fp);
            
            if (strcmp(open, "") == 0){
                sprintf(temp6, "%u", i / 16 + 1); 
                return temp6;
            }
        }
	    return "-1"; 
    }
    if(selection == 2){
        char cmpName[12];
        fseek(fp, BLOCKSIZE * INFOSECOFFSET , SEEK_SET); 
        for(int i = 0; i < DATAOFFSET * BLOCKSIZE; i+= 64){
            fseek(fp, BLOCKSIZE * INFOSECOFFSET + i, SEEK_SET);
            fread(cmpName, 12, 1, fp);
            
            if (strcmp(cmpName, "") == 0){
                sprintf(temp6, "%u", (i / 64 * 4) + (BLOCKSIZE * INFOSECOFFSET / 16) + 1);
                return temp6;
            }
        }
        return "-1"; 
    }
    if(selection == 3){
        char open[1]; 
        fseek(fp, BLOCKSIZE * DATAOFFSET, SEEK_SET);
        for(int i= 0; i <= (TOTALBLOCKS - 3) * 512 ; i+= 512){
            fseek(fp, BLOCKSIZE * DATAOFFSET + i, SEEK_SET);
            
            fread(open, 1, 1, fp); 
            if(strcmp(open, "") == 0){ 
                sprintf(temp6, "%u", (i / 512 * 32) + (BLOCKSIZE * DATAOFFSET / 16) + 1);
                return temp6;
            }
        }
        return "-1";
    }
    else{
        printf("Error Invalid");
        return "-1";
    }
}

/*
--FIND FILE FUNCTION--

DESCRIPTION:
	- Find File locates a file based on its respected name
	- Traverses info sections to compare name with file name
	- Return the file indicator value

PARAMETERS:
	*fileName -- Character pointer to the file name

RETURN:
	fileIndicator -- Index value
	-1 -- If an error occurs
*/

int findFile(char *fileName){
	char cmpName[12];
	int fileIndicator = 0;
	
	fseek(fp, 0, SEEK_SET);	
	for(int i = 0; i < (INFOSECOFFSET * BLOCKSIZE); i+= 32){
		fseek(fp, i + 1, SEEK_SET);
		fread(cmpName,12, 1, fp);
		
		if (strcmp(cmpName, fileName) == 0){
			fileIndicator = i / 16 + 1; 
			return fileIndicator;
		}
	}
	return -1; 
}

/*
--GET DATE TIME FUNCTION--

DESCRIPTION:
	- Get date time is resonsible for retrieving the current date or time using the time.h header file
	- Depending on selection the funciton will return the year, month, day, hour, minute, or second.
	- Return value is the result of whatever value you need

PARAMETERS:
	choice -- Selection of which value you need to obtain

RETURN:
	temp(#) -- Date or time value
	-1 -- If an error occurs
*/

char *getDateTime(int choice){ 
	time_t now;
	struct tm *tm;

	now = time(0);

	if((tm = localtime(&now)) != NULL){
		if (choice == 1){	
			sprintf(temp4, "%04d", tm->tm_year + 1900);
			return temp4;
		}
		else if (choice == 2){ 
			sprintf(temp2, "%02d", tm->tm_mon + 1);
			return temp2;
		}
		else if (choice == 3){	
			sprintf(temp2, "%02d", tm->tm_mday);
			return temp2;
		}
        else if (choice == 4){	
			sprintf(temp2, "%02d", tm->tm_hour);
			return temp2;
		}
		else if (choice == 5){	
			sprintf(temp2, "%02d", tm->tm_min);
			return temp2;
		}
		else if (choice == 6){	
			sprintf(temp2, "%02d", tm->tm_sec);
			return temp2;
		}
		else {
			return "-1";
		}
	}

}

/*
--CREATE FILE FUNCTION--

DESCRIPTION:
	- Create file function is used to create a file or a directory depending on if the alarm receives a specific value
	- Begin by initializing some temporary indicator values
	- Set each indicator to respective blank space addresses
	- Seek to each section and allocate each struct with proper informaiton accordingly
	- If the alarm is passed a 1 we outfit the info section with a DIR identifier
	- Else we populate with the extension
	- Next initialize the data blocks and assign it as the current directory if needed

PARAMETERS:
	*fileName -- Pointer to the name of the file
	alarm -- integer bit to represent whether it is or isn't a directory

RETURN:
	None -- Void Function
*/

void createFile(char *fileName, int alarm){
	char *retrunIndicator;
	char *fatIndicator;
	char *infoSecIndicator;
	char *dataIndicator; 
	
	fatIndicator = strdup(findFreeSpace(1));	
	
	infoSecIndicator = strdup(findFreeSpace(2));	
	
	dataIndicator = strdup(findFreeSpace(3));

	fseek(fp, (atol(fatIndicator) - 1) * 16, SEEK_SET); 

	struct fat newFile = {""};

	strcpy(newFile.open, "1");
	strcpy(newFile.fileName, fileName);
	strcpy(newFile.infoSecRef, infoSecIndicator);
	strcpy(newFile.dataRef, dataIndicator);
	strcpy(newFile.nextRef, "-1");

	fwrite(&newFile, sizeof(struct fat), 1, fp);
	
	fseek(fp, (atol(infoSecIndicator) - 1) * 16, SEEK_SET); 				

	struct infoSec newinfoSec = {""};										

	strcpy(newinfoSec.fileName, fileName);

	if (alarm == 1){
		strcpy(newinfoSec.extension, "DIR"); 
	}
	else {
        char ext[3];
        for(int z = 0; fileName[z] != '\0'; z++){
            if(fileName[z] == '.'){
                ext[0] = fileName[z+1];
                ext[1] = fileName[z+2];
                ext[2] = fileName[z+3];
                break;
            }
        }
		strcpy(newinfoSec.extension, ext);
	}

	strcpy(newinfoSec.creationYear, getDateTime(1));
	strcpy(newinfoSec.creationMonth, getDateTime(2));
	strcpy(newinfoSec.creationDay, getDateTime(3));	
	strcpy(newinfoSec.creationHour, getDateTime(4));
	strcpy(newinfoSec.creationMinute, getDateTime(5));
	strcpy(newinfoSec.creationSecond, getDateTime(6));
	strcpy(newinfoSec.modificationYear, getDateTime(1));
	strcpy(newinfoSec.modificationMonth, getDateTime(2));
	strcpy(newinfoSec.modificationDay, getDateTime(3));	
	strcpy(newinfoSec.modificationHour, getDateTime(4));
	strcpy(newinfoSec.modificationMinute, getDateTime(5));
	strcpy(newinfoSec.modificationSecond, getDateTime(6));
	strcpy(newinfoSec.fileSize, "000000");

	fwrite(&newinfoSec, sizeof(struct infoSec), 1, fp);
	
	fseek(fp, (atol(dataIndicator) - 1) * 16, SEEK_SET); 	
	fputs(".", fp);										
	
	int i = 0;
	int found = 0;
	char open[1];

	while(i < 32){
		fseek(fp, currentDirectory + (i * 16), SEEK_SET);
		fread(open, 1, 1, fp); 
		if(strcmp(open, "") == 0){ 	
			fseek(fp, -1, SEEK_CUR);	
			fwrite(fileName, 12, 1, fp);
			break;	
		}
		i++;
	}
	
	if (alarm == 1){
		currentDirectory = (atol(dataIndicator) - 1) * 16 ;
	}
}

/*
--DELETE FILE FUNCTION--

DESCRIPTION:
	- Delete File function begins by initializing some reference values to be used throughout the search and deletion
	- We then find the file we are looking to delete
	- We seek and clear the FAT entry, infosec entry, and all associated data blocks
	- Essentially overwriting the entry with clear information 

PARAMETERS:
	*fileName -- Pointer to the name of the file

RETURN:
	None -- Void Function
*/

void deleteFile(char *fileName){
	int fileIndicator = 0;
	char dataRef[6];
	char infoSecRef[6];
	char entryName[13] = {'\0'};

	fileIndicator = findFile(fileName); 

	fseek(fp, (fileIndicator - 1) * 16, SEEK_SET);	
	fseek(fp, 19, SEEK_CUR);					
	fread(dataRef, 1, 6, fp);
	fseek(fp, (atol(dataRef) - 1) * 16, SEEK_SET);
	struct data clearBlock = {""};  
	fwrite(&clearBlock, sizeof(struct data), 1, fp);

	fseek(fp, (fileIndicator - 1) * 16, SEEK_SET);	
	fseek(fp, 13, SEEK_CUR);					
	fread(infoSecRef, 1, 6, fp);
	fseek(fp, (atol(infoSecRef) - 1) * 16, SEEK_SET);
	struct infoSec clearinfoSec = {""}; 
	fwrite(&clearinfoSec, sizeof(struct infoSec), 1, fp);

	fseek(fp, (fileIndicator - 1) * 16, SEEK_SET);	
	struct fat clearfat = {""};
	fwrite(&clearfat, sizeof(struct fat), 1, fp);

	for(int i = 0; i < 32; i++){
		fseek(fp, currentDirectory + (i * 16), SEEK_SET);
		fread(entryName, 1, 12, fp);
		if (strcmp(entryName, fileName) == 0){
			fseek(fp, currentDirectory + (i * 16), SEEK_SET);
			struct line clearline = {""};
			fwrite(&clearline, sizeof(struct line), 1, fp);
		}
	}
}

/*
--OPEN FILE FOR READING FUNCTION--

DESCRIPTION:
	- The open file for reading function allows the user to read a file but not make changes to it.
	- Indicators and references are initialized and a find file call locates the file by file name
	- Seek through to the data sections and print all values held within the file
	- Function ends when all values are printed

PARAMETERS:
	*fileName -- Pointer to the name of the file

RETURN:
	None -- Void Function
*/

void openFileRead(char *fileName){
	int fileIndicator = 0;
	char buffer[512];
	char dataRef[6];
	long dataRefAsNum;

	fileIndicator = findFile(fileName); 

	fseek(fp, (fileIndicator - 1) * 16, SEEK_SET);	

	fseek(fp, 19, SEEK_CUR); 					
	fread(dataRef , 1, 6, fp); 					
	dataRefAsNum = atol(dataRef); 				

	fseek(fp, (dataRefAsNum - 1) * 16, SEEK_SET);
	fread(buffer, 1, 512, fp);

	for (int i = 0; i < 512; i++){
		printf("%c", buffer[i]);
	}
	printf("\n");
}

/*
--OPEN FILE FOR WRITING FUNCTION--

DESCRIPTION:
	- The open file for writing funciton is used for opening a file previously created within the file system for modification
	- First indicators and references are initialized as placeholders
	- Next the file is located within the system
	- We then seek to the data blocks to begin making adjustments based on need.
	- Data is appended from parameters to the file

PARAMETERS:
	*fileName -- Pointer to the name of the file
	*toWrite -- Pointer to the content being written to the file

RETURN:
	None -- Void Function
*/

void openFileWrite(char *fileName, char *toWrite){
	int fileIndicator = 0;
	int inputLength = 0;
	char dataRef[6];
	long dataRefAsNum; 

	fileIndicator = findFile(fileName); 
	
	inputLength = strlen(toWrite);

	if(inputLength >= 512){	
		return;	
	}

	fseek(fp, (fileIndicator - 1) * 16, SEEK_SET);

    //fseek(fp, 13, SEEK_CUR);


	fseek(fp, 19, SEEK_CUR); 					

	fread(dataRef , 1, 6, fp); 					
	dataRefAsNum = atol(dataRef); 				

	fseek(fp, (dataRefAsNum - 1) * 16, SEEK_SET);
	fwrite(toWrite, 1, BLOCKSIZE, fp);
}

/*
--CHANGE DIRECTORY FUNCTION--

DESCRIPTION:
	- The change directory funciton allows for virtualization of the file system in that directories can be changed within the file structure
	- Begin with indicators and references
	- Find the directory in the file system
	- Change all references to that of the new directory and return on success

PARAMETERS:
	*fileName -- Pointer to the name of the file

RETURN:
	None -- Void Function
*/

void changeDirectory(char *fileName){
	int fileIndicator = 0;
	char extension[3];
	char infoSecRef[6];
	char dataRef[6];

	fileIndicator = findFile(fileName); 
	
	fseek(fp, (fileIndicator - 1) * 16, SEEK_SET);	
	fseek(fp, 13, SEEK_CUR); 					
	fread(infoSecRef, 1, 6, fp);

	fseek(fp,(atol(infoSecRef) - 1) * 16, SEEK_SET);

	fseek(fp, 12, SEEK_CUR);					

	fread(extension, 1, 3, fp);
	if(strcmp(extension, "DIR") != 0){
		return;
	}
	fseek(fp, (fileIndicator - 1) * 16, SEEK_SET);	
	fseek(fp, 19, SEEK_CUR); 					

	fread(dataRef, 1, 6, fp);
	currentDirectory = (atol(dataRef) -1)* 16;

}

/*
--FILE INFORMATION FUNCTION--

DESCRIPTION:
	- The file information function is used to display informaiton about a particular file in the system
	- Information is populated for the name, extension, creation date, and modification date
	- A series of seek and read calls generates this information

PARAMETERS:
	*fileName -- Pointer to the name of the file

RETURN:
	None -- Void Function
*/

void fileInfo(char *fileName){
	char name[13] = {'\0'};
	char extension[4] = {'\0'};
	char cyear[5] = {'\0'};
	char cmonth[3] = {'\0'};
	char cday[3]= {'\0'};
	char chour[3]= {'\0'};
	char cminute[3]= {'\0'};
	char csecond[3]= {'\0'};
    char myear[5] = {'\0'};
	char mmonth[3] = {'\0'};
	char mday[3]= {'\0'};
	char mhour[3]= {'\0'};
	char mminute[3]= {'\0'};
	char msecond[3]= {'\0'};

	int fileIndicator = 0;
	char infoSecRef[6];
	long infoSecRefAsNum;

	fileIndicator = findFile(fileName); 
	if (fileIndicator == -1){	
		return;
	}
	fseek(fp, (fileIndicator - 1) * 16, SEEK_SET);	
	fseek(fp, 13, SEEK_CUR); 					

	fread(infoSecRef , 1, 6, fp); 					
	infoSecRefAsNum = atol(infoSecRef); 				

	fseek(fp,(infoSecRefAsNum - 1) * 16, SEEK_SET);	

	fread(name, 1, 12, fp);
	fread(extension, 1, 3, fp);
	fread(cyear, 1, 4, fp);
	fread(cmonth, 1, 2, fp);
	fread(cday, 1, 2, fp);
	fread(chour, 1, 2, fp);
	fread(cminute, 1, 2, fp);
	fread(csecond, 1, 2, fp);
    fread(myear, 1, 4, fp);
	fread(mmonth, 1, 2, fp);
	fread(mday, 1, 2, fp);
	fread(mhour, 1, 2, fp);
	fread(mminute, 1, 2, fp);
	fread(msecond, 1, 2, fp);
    

	printf("File Name -- %s\n", name);
	printf("Extension -- %3s\n", extension);
	printf("Created -- %s-%s-%s at %s:%s:%s \n", cmonth, cday, cyear, chour, cminute, csecond);
	printf("Modified -- %s-%s-%s at %s:%s:%s \n", mmonth, mday, myear, mhour, mminute, msecond);
}

/*
--DIRECTORY LIST FUNCTION--

DESCRIPTION:
	- The Directory List function is responsible for listing the contents of directories
	- Called on the current directory, the function seeks and reads all contents
	- The function returns when all contents are listed

PARAMETERS:
	None -- Void Function

RETURN:
	None -- Void Function
*/

void directoryList(){
	char fileName[13] = {'\0'};

	for(int i = 0; i < 32; i++){
		fseek(fp, currentDirectory + (i * 16), SEEK_SET);	
		fread(fileName, 1, 12, fp);
		printf("%s   ", fileName);
	}
	printf("\n");
}

/*
--LEAVE FUNCTION--

DESCRIPTION:
	- The Leave function allows the user to close the file system and leave the program

PARAMETERS:
	None -- Void Function

RETURN:
	None -- Void Function
*/

void leave(){ 
	fclose(fp);
	exit(0);
}