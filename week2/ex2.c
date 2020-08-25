#include <stdio.h>
#include <string.h>

#define MAX_LEN 255

int main()
{
	char str[MAX_LEN];
	
	printf("Enter an string\n");
	fgets(str, MAX_LEN, stdin);

	printf("Reversed string:\n");
	for (int i = strlen(str) - 2; i >= 0; --i) {
		printf("%c", str[i]);
	}
	printf("\n");
	
	return 0;
}
