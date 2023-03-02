#include "main.h"

/**
 * more_numbers - prints 10 times the numbers, from 0 to 14
 * Return : void
 */
void more_numbers(void)
{
	int i, j;

	for (i = 0; i < 10; i++)
	{
		for (j = 0; j <= 14; j++)
		{
			(j > 9) ? _putchar((j / 10) + '0') : 0;
			_putchar((j % 10) + '0');
		}
		_putchar('\n');
	}
}
