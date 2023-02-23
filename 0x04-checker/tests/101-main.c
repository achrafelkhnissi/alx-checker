#include "../main.h"

/**
* main - Tests the print_number function
* Return: Always 0 (Success)
*/
int main(void)
{
	print_number(98);
	_putchar('\n');
	print_number(402);
	_putchar('\n');
	print_number(1024);
	_putchar('\n');
	print_number(0);
	_putchar('\n');
	print_number(-98);
	_putchar('\n');
	print_number(-2147483648);
	_putchar('\n');
	print_number(2147483647);
	_putchar('\n');


	return (0);
}
