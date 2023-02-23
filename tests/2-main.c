#include "../main.h"
#include <stdio.h>

/*
 * test_mul - test the mul function
 * @a: first integer
 * @b: second integer
 * Return: void
 */
void test_mul(int a, int b)
{
	printf("%d * %d = %d\t| Your result: %d\t| [%s]\n", a, b, a * b, mul(a, b), (a * b == mul(a, b)) ? "OK" : "KO");
}

/**
 * main - entry point
 * Return: 0
 */
int main(void)
{
	/* Tests for mul */
	test_mul(98, 1024);
	test_mul(-402, 4096);
	test_mul(1024, -98);
	test_mul(-1024, -98);

	return (0);
}
