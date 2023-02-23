#include "../main.h"
#include <stdio.h>
#include <ctype.h>

/*
 * test_isdigit - test the _isdigit function
 * @c: value to be checked
 * Return: void
 */
void test_isdigit(int c)
{
	printf("%c is %s\t| ", c, isdigit(c) ? "digit" : "not digit");
	printf("Your function says: %s\t| ", _isdigit(c) ? "digit" : "not digit");
	printf("[%s]\n", isdigit(c) == _isdigit(c) ? "OK" : "KO");
}

/**
 * main - entry point
 * Return: 0
 */
int main(void)
{
	/* Tests for _isdigit */
	test_isdigit('A');
	test_isdigit('a');
	test_isdigit('Z');
	test_isdigit('z');
	test_isdigit('0');
	test_isdigit('9');
	test_isdigit(' ');
	test_isdigit(65);

	return (0);

}
