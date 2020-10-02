#include <stdio.h> 
#include <fcntl.h> 
#include <errno.h>
#include <sys/stat.h>

extern int errno; 

void printFileStatsInformation (char* fileName)
{
	struct stat fileStat;
	stat(fileName, &fileStat);
	
	printf("\n====================================\n");
	printf("Information for %s\n",fileName);
	printf("---------------------------\n");
	printf("File Size: \t\t%d bytes\n",fileStat.st_size);
	printf("Number of Links: \t%d\n",fileStat.st_nlink);
	printf("File inode: \t\t%d\n",fileStat.st_ino);
	printf("File Permissions: \t");
	printf( (S_ISDIR(fileStat.st_mode)) ? "d\n" : "-\n");
	printf("======================================\n\n");
}

int main () {
    char file_input_path[10000];
    char file_output_path[10000];
    
    printf("Enter the source file path: ");
    scanf("%s", &file_input_path);
    
    printf("Enter the destination file path: ");
    scanf("%s", &file_output_path);
    
    // INPUT
    int fileInputDescripter = open(file_input_path, O_RDONLY);
    
    if (fileInputDescripter < 0) {
        perror("Message for Input File"); 
        return 1;
    }
    
    // PRINT INPUT STATS INFORMATION
    printFileStatsInformation(file_input_path);
    
    // OUTPUT
	int fileOutputDescripter = open(file_output_path, O_WRONLY | O_CREAT);
    
    if (fileOutputDescripter < 0) {
        perror("Message for Output File"); 
        return 1;
    }
    
    char file_buffer;
    while(read(fileInputDescripter, &file_buffer, 1))
        write(fileOutputDescripter, &file_buffer, 1);
        
    
    close(fileInputDescripter);
    close(fileOutputDescripter);
    
    printf("Successfully copy file from %s to %s\nThank you", file_input_path, file_output_path);
    
    return 0;
}
