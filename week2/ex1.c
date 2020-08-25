#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
	int a = INT_MAX;
	float b = FLT_MAX;
	double c = DBL_MAX;

	printf("int: \n value: %d, size: %lu \n\n", a, sizeof(a));
	printf("float: \n value: %f, size: %lu \n\n", b, sizeof(b));
	printf("double: \n value: %lf, size: %lu \n", c, sizeof(c));

	return 0;
}
