#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

int main(void)
{
	int test[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	struct timeval *start = malloc(sizeof(struct timeval));
	for (int i = 0; i < 100000; i++)
	{
		gettimeofday(start, NULL);
		test[start->tv_usec % 10] += 1;
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%d: %f\n", i, (double)test[i] * 100 / 100000);
	}
	return (0);
}