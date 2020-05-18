#ifndef FILESYS_H_
#define FILESYS_H_

FILE setup();
//int closefs(FILE *fp);
void createFile(char *fileName, int alarm);
void deleteFile(char *fileName);
void openFileRead(char *fileName);
void openFileWrite(char *fileName, char *toWrite);
void changeDirectory(char *fileName);
void fileInfo(char *fileName);
void directoryList();
void leave();

#endif