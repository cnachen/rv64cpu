#include <math.h>

int test(int n)
{
	static int i = 0;
	return ++i + n;
}

int start()
{
	int sum = 0;
	for (int i = 0; i < 2; i++)
		sum += test(114514);
	return sum;
}
