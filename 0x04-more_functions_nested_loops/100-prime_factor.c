#include <stdio.h>

/**
 * main - prints the largest prime factor of the number 612852475143
 *
 * Description:
 *		- A factor is a number that can be evenly divided into another number.
 *			For example, the factors of 6 are 1, 2, 3, and 6.
 *		- A prime factor is a factor that is also a prime number, which means
 *			it can only be divided by 1 and itself. For example, the prime
 *			factors of 6 are 2 and 3.
 *
 * Return: 0
 */
int main(void)
{
	long int n = 612852475143;
	long int i;

	for (i = 2; i < n; i++)
	{
		while (n % i == 0)
			n /= i;
	}

	printf("%ld\n", n);

	return (0);
}
