#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(){
    FILE* fp = stdout;

    char buffer[100];
    setvbuf(stdout, buffer, _IOLBF, sizeof(buffer));

    fprintf(fp, "H");
    sleep(1);
    fprintf(fp, "e");
    sleep(1);
    fprintf(fp, "l");
    sleep(1);
    fprintf(fp, "l");
    sleep(1);
    fprintf(fp, "o");
    sleep(1);
    fprintf(fp, "\n");

    fclose(fp);

    return 0;
}