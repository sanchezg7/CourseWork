#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/stat.h>

int main( int argc, char** argv){
	assert(argc == 2);
	char* targetName = argv[1]; //can be directory or file
	
	
	struct stat mystat;
	stat(targetName, &mystat);
	//stat() gets metadata for a file
  printf("  File: `%s'\n", targetName);
  printf("  Size: %jd\t\tIO Blocks: %jd\n", mystat.st_size, mystat.st_blocks);
  printf("Inode: %jd \tLinks: %jd\n", mystat.st_ino, mystat.st_nlink);

  printf("Access: (");

  //st_mode is a word with several flags
  //mask the particular flags (bit positions)to check and see if they are valid or not
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
  printf(")\n");
	
	
	return 0;
}
/* 
struct stat {
	dev_t st_dev; / * ID of device containing file * /
	ino_t st_ino; / * inode number * /
	mode_t st_mode; / * protection * /
	nlink_t st_nlink; / * number of hard links * /
	uid_t st_uid; / * user ID of owner * /
	gid_t st_gid; / * group ID of owner * /
	dev_t st_rdev; / * device ID (if special file) * /
	off_t st_size; / * total size, in bytes * /
	blksize_t st_blksize; / * blocksize for filesystem I/O * /
	blkcnt_t st_blocks; / * number of blocks allocated * /
	time_t st_atime; / * time of last access * /
	time_t st_mtime; / * time of last modification * /
	time_t st_ctime; / * time of last status change * /
};
*/
