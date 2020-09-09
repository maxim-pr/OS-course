#include <stdio.h>
#include <stdlib.h>

int main(){
	char s[100];

  printf("Write commands without parameters in column\n");
  printf("Use ctrl+C to exit");
  
	while(1){
		scanf("%100s",s);
		system(s);
	}

	return 0;
}
