#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[]){
    
    int fd = open("ex1.txt", O_RDWR); // open file

    if(fd < 0){
        printf("Could not open ex1.txt\n");
        return 1;
    }

    char* str = "This is a nice day\n";

    ftruncate(fd, strlen(str)); // change size of the file
    
    char *ptr = mmap(NULL,strlen(str),
            PROT_READ|PROT_WRITE,
            MAP_SHARED,
            fd,0);

    if(ptr == MAP_FAILED){
        printf("Mapping Failed\n");
        return 1;
    }

    strncpy(ptr,str,strlen(str)); // write

    close(fd);

    int err = munmap(ptr, strlen(str));

    if(err != 0){
        printf("UnMapping Failed\n");
        return 1;
    }
    return 0;
}
