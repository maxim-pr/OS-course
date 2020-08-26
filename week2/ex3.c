#include <stdio.h>

int main(int argc, char* argv[])
{
	int n;

	sscanf(argv[1], "%d", &n);

	if (n < 1) {
		printf("Wrong n\n");
		return -1;
	}

	int nstars = 1;  // current number of stars in the row

	for (int i = 0; i < n; ++i) {
		for (int k = 0; k < (n - (1 + nstars) / 2); ++k)
			printf(" ");

		for (int j = 0; j < nstars; ++j)
			printf("*");

		for (int k = 0; k < (n - (1 + nstars) / 2); ++k)
			printf(" ");

		printf("\n");

		// number of stars in the rows are odd,
		// so increase current number of stars by 2
		nstars += 2;
	}

	return 0;
}
