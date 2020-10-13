#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>


int hit = 0;
int miss = 0;



struct pageFrame
{
	unsigned int empty;
	unsigned int r; // referenced bit
	unsigned int counter; 
	int id;
};


int indexInMemory(int n, struct pageFrame* pageFrames, int page)
{
	int index = -1;

	for (int i = 0; i< n; i++) {
		if (pageFrames[i].empty == 0 && pageFrames[i].id == page)
			return i;
	}

	return -1;
}

void processMemReference(int n, int* k, struct pageFrame* pageFrames, int page) 
{
	// process tick end: for each page, the counter is shifted right 1 bit,
	// and the R bit is added to the leftmost bit.
	// R bit is reset
	for (int i = 0; i < n; i++) {
		if (pageFrames[i].empty == 0) {
			pageFrames[i].counter = pageFrames[i].counter >> 1;
			if (pageFrames[i].r == 1) {
				pageFrames[i].counter += 1 << 15; 
				pageFrames[i].r = 0;
			}
		}
	}


	// process incoming page reference
	int ind = indexInMemory(n, pageFrames, page);
	// if referenced page is in memory, just set its R bit to 1
	if (ind != -1) {
		hit++;

		pageFrames[ind].r = 1;
	}
	// otherwise, a page fault occured
	else {
		miss++;


		// if there is free space in memory, just insert the page (from disk)
		if (*k < n) {
			for (int i = 0; i < n; i++) {
				if (pageFrames[i].empty == 1) {
					pageFrames[i].empty = 0;
					pageFrames[i].id = page;
					pageFrames[i].r = 1;
					pageFrames[i].counter = 0;
					break;
				}
			}

			*k += 1;
		}
		// otherwise, there is a need to evict some page with the lowest counter
		else {
			unsigned int lowestCounter = UINT_MAX;
			int indOfLowestCounter = -1;

			for (int i = 0; i < n; i++) {
				if (pageFrames[i].counter < lowestCounter) {
					lowestCounter = pageFrames[i].counter;
					indOfLowestCounter = i;
				}
			}


			pageFrames[indOfLowestCounter].id = page;
			pageFrames[indOfLowestCounter].r = 1;
			pageFrames[indOfLowestCounter].counter = 0;
		}
	}
}


void printNum(unsigned int a)
{
	unsigned int b = a;
	while (b > 0) {
		printf("%d", b % 10);
		b /= 10;
	}
}

int main(int argc, char const *argv[])
{

	FILE* input = fopen("input.txt", "r");


	printf("Enter number of page frames: ");
	unsigned int n; // number of page frames
	scanf("%u", &n);
	printf("\n");


	struct pageFrame* pageFrames = (struct pageFrame*)malloc(n * sizeof(struct pageFrame)); // page table


	// initialize all page frames as empty
	for (int i = 0; i < n; i++) {
		pageFrames[i].empty = 1;
		pageFrames[i].r = 0;
		pageFrames[i].counter = 0;
		pageFrames[i].id = -1;
	}

	int nonemptyFrames = 0; // number of pages in physical memory (nonempty frames)


	int nreferences; // number of page references
	printf("Enter number of page references: ");
	scanf("%d", &nreferences);
	printf("\n");


	for (int i = 0; i < nreferences; i++) {
		int currPage;
		fscanf(input, "%d", &currPage);

		processMemReference(n, &nonemptyFrames, pageFrames, currPage);
	}

	printf("Hits: %d\n", hit);
	printf("Misses: %d\n", miss);

	fclose(input);

	return 0;
}