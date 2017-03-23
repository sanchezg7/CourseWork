#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h> //for strcmp
#include <unistd.h> //for getcwd
#include <sys/stat.h>
#include <dirent.h> //library for directories
#include <pwd.h>
//assume max path length 256
#define MAX_LENGTH 256

//interfaces stat(), opendir(), readdir(), getcwd()

void printDetailed(char* directory); //calls stat on each dirent in the directory
void printGeneral(char* directory); //only brief info about the files in directory
void printDetailed(char* directory);
void printPermissions(struct stat mystat);

int main (int argc, char** argv) {
	//if argv[1] == "-l", check if argc == 3 (directory provided), or argc == 2(use current directory)
	//set current directory initially, and change it if argc == 3 or if argv[1] != "-l"
	//no arguments -- print all file names (struct stat name)
	char* directory;
  


  
    if (argc == 3){ //detailed on SPECIFIC directory
      //printf("Directory provided: ");
      directory = (char *) malloc(sizeof(char) * strlen(argv[2]));
      strcpy(directory, argv[2]);
      //puts(directory);
      printDetailed(directory);
            
    } else if (argc == 2) { //either "-l" or "cwd"

        if (!strcmp(argv[1], "-l")) {

          //printf("-l here\nCurrent Directory");
          //call stat on each file and print accordingly
          directory = (char *) malloc(sizeof(char*) * MAX_LENGTH);
          assert(directory);
          getcwd(directory, MAX_LENGTH);
          assert(directory);
          printDetailed(directory);
        } else { //brief on SPECIFIC directory
            directory = (char *) malloc(sizeof(char) * strlen(argv[1]));
            assert(directory);
            strcpy(directory, argv[1]);
            assert(directory);
            printGeneral(directory); 
          }
      } 
      else { //current directory without l
        directory = (char *) malloc(sizeof(char*) * MAX_LENGTH);
        assert(directory);
        getcwd(directory, MAX_LENGTH);
        assert(directory);
        printGeneral(directory);

      }

	return 0;
}
  


//struct dirent {
//    ino_t          d_ino;       /* inode number */
//    off_t          d_off;       /* offset to the next dirent */
//    unsigned short d_reclen;    /* length of this record */
//    unsigned char  d_type;      /* type of file; not supported
//                                   by all file system types */
//    char           d_name[256]; /* filename */
//};


  
DIR* getTargetDirectory(  char* directory) //declares the descriptor for the directory
{ 
  DIR* targetDirectory; //holds descriptor for directory
  //printf("Operation successful\n");
  //puts(directory);
  targetDirectory = opendir(directory);
  assert(targetDirectory);
  return targetDirectory; //return the directory descriptor pointer
}
void printPermissions(struct stat mystat)
{
	printf( (S_ISDIR(mystat.st_mode)) ? "d" : "-"); //is it a directory?
	printf( (mystat.st_mode &S_IRUSR) ? "r" : "-"); //user read
	printf( (mystat.st_mode &S_IWUSR) ? "w" : "-"); //user write
	printf( (mystat.st_mode &S_IXUSR) ? "x" : "-"); //user execute
	printf( (mystat.st_mode &S_IRGRP) ? "r" : "-"); //group read
	printf( (mystat.st_mode &S_IWGRP) ? "w" : "-"); //group write
	printf( (mystat.st_mode &S_IXGRP) ? "x" : "-"); //group execute
	printf( (mystat.st_mode &S_IROTH) ? "r" : "-"); //other read
	printf( (mystat.st_mode &S_IWOTH) ? "w" : "-"); //other write
	printf( (mystat.st_mode &S_IXOTH) ? "x" : "-"); //other execute
    
}
void printDetailed(  char* directory){  //calls stat on each dirent in the directory

  DIR* targetDirectory = getTargetDirectory(directory);
  struct dirent* currentFile;
  struct stat mystat;
  struct passwd* user;
  struct passwd* group;
  char* fileName = NULL;


  while((currentFile = readdir(targetDirectory)) != NULL)
  {
    
    fileName = (char *) malloc(sizeof(char) * strlen(currentFile->d_name));
    assert(fileName);
    strcpy(fileName, currentFile->d_name);
    stat(fileName, &mystat);

    printPermissions(mystat);
    user = getpwuid(mystat.st_uid);
    group = getpwuid(mystat.st_gid);
    //matching format of LS, used st_size(size of file), rather than IO blocks
    printf(" %s %s %*jd %s\t\n", user->pw_name, group->pw_name, 6, mystat.st_size,  fileName);
    free(fileName);
  }
}


void printGeneral(char* directory){  //only name info about the files in directory
  DIR* targetDirectory = getTargetDirectory(directory);
  struct dirent* currentFile;
  struct stat mystat;
  char* fileName = NULL;

  //printf("File Name\n");
  while((currentFile = readdir(targetDirectory)) != NULL)
  {

    fileName = (char *) malloc(sizeof(char) * strlen(currentFile->d_name));
    assert(fileName);
    strcpy(fileName, currentFile->d_name);
    stat(fileName, &mystat);
    printf("%s\n", fileName);
    free(fileName);
  }

  
}
  	

