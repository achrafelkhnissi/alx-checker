#include "main.h"

/**
 * print_number - prints an integer using only _putchar
 * @n : integer to print
 *
 * Return: void
 */
void print_number(int n)
{
	unsigned int num = n;

	if (n < 0)
	{
		_putchar('-');
		num = n * -1;
	}

	if (num > 9)
		print_number(num / 10);

	_putchar(num % 10 + '0');
}
