#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#define MAX_LENGTH 256


void traverseDirectory(char* globalpath, int tabs);
DIR* getDirectory (char* path);

char* mainDirectory;

int main( int argc, char** argv){

	//open directory, if provided
	//else use cwd
	//read dir until null
	//if null, return
	//stat the file
	//if the "file" is a directory, call the function to search
	//	return when null

	mainDirectory = malloc(sizeof(char) * MAX_LENGTH);
	getcwd(mainDirectory, MAX_LENGTH);

	if(argc == 2){
		strcpy(mainDirectory, argv[1]);
	} 
	//printf("Main Directory: ");
	
	puts(mainDirectory);
	traverseDirectory(mainDirectory, 1);
	//printf("Done!\n");	
	return 0;
}



void traverseDirectory(char* globalpath, int tabs) //with respect to a SINGLE directory
{
	DIR* thisDirectory = opendir(globalpath);
	assert(thisDirectory);
	//printf("thisDirectory -- path: %s\n", globalpath);
	struct dirent* thisFile;
	struct stat myStat;
	char* path = malloc (sizeof(char) * strlen(globalpath));
	char* currentFileName;
	int i;
	strcpy(path, globalpath);


	while((thisFile = readdir(thisDirectory)) != NULL)
	{	
		if((strcmp(thisFile->d_name, ".") ==0) || strcmp(thisFile->d_name, "..") == 0)
				continue;	
		currentFileName = malloc(sizeof(char) * (strlen(thisFile->d_name) + strlen(path) + 1));
		assert(currentFileName);
		strcat(currentFileName, path);
		strcat(currentFileName, "/");
		strcat(currentFileName, thisFile->d_name);		
				
		//printf("fileName~ %s\n", currentFileName);
		//need path of the directory
		assert(stat(currentFileName, &myStat) != -1);
		//printf("ID: %jd\n", myStat.st_ino);
	
		if(S_ISDIR(myStat.st_mode))
		{
			for(i = 0; i < tabs; ++i) printf(" ");
			printf("%s -- \n", thisFile->d_name);
			
			traverseDirectory(currentFileName, tabs+1); //include number of iteration to keep track of tabs for visual appreciwtion
			
		} else {
			for(i = 0; i < tabs; ++i) printf(" ");
			printf("%s\n", thisFile->d_name);
		}
		strcpy(currentFileName, "");
		//printf("Freed currentFileName, going to next name\n");
		
	}	
	
	return;

}

