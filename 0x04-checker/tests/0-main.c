#include "../main.h"

#include <stdio.h>
#include <ctype.h>

/**
 * test_isupper - A funciton to test _isupper
 * @c: value to be checked
 * Return: void
 */
void test_isupper(int c)
{
	printf("%c is %s\t| ", c, isupper(c) ? "upper" : "not upper");
	printf("Your function says: %s\t| ", _isupper(c) ? "upper" : "not upper");
	printf("[%s]\n", isupper(c) == _isupper(c) ? "OK" : "KO");
}

/**
 * main - entry point
 * Return: 0
 */
int main(void)
{
	/* Tests for _isupper */
	test_isupper('A');
	test_isupper('a');
	test_isupper('Z');
	test_isupper('z');
	test_isupper('0');
	test_isupper('9');
	test_isupper(' ');
	test_isupper(65);

	return (0);
}
