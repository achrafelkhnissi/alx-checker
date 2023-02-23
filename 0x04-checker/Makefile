CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c89
TESTDIR=tests
OUTPUTDIR=correct_outputs

# Define variables for colors
PURPLE = \033[1;35m
NO_COLOR = \033[0m
GREEN = \033[0;32m
RED = \033[0;31m

OK=$(GREEN)[OK]$(NO_COLOR)
FAIL=$(RED)[FAIL]$(NO_COLOR)

.PHONY: all 0 1 2 3 4 5 6 7 8 9 10 100 101 clean

all:
	@echo "Usage: make [task number]"

check-all: 0 1 2 3 4 5 6 7 8 9 10 100 101

betty:
	@echo "\n$(PURPLE)Running betty-style...\n$(NO_COLOR)"
	@echo -n "main.h: "
	@betty main.h | if [ $$? -eq 0 ]; then echo "\t\t$(OK)"; else echo "\t\t$(FAIL)"; fi
	@echo -n "0-isupper.c: "
	@betty 0-isupper.c | if [ $$? -eq 0 ]; then echo "\t\t$(OK)"; else echo "\t\t$(FAIL)"; fi
	@echo -n "1-isdigit.c: "
	@betty 1-isdigit.c | if [ $$? -eq 0 ]; then echo "\t\t$(OK)"; else echo "\t\t$(FAIL)"; fi
	@echo -n "2-mul.c: "
	@betty 2-mul.c | if [ $$? -eq 0 ]; then echo "\t\t$(OK)"; else echo "\t\t$(FAIL)"; fi
	@echo -n "3-print_numbers.c: "
	@betty 3-print_numbers.c | if [ $$? -eq 0 ]; then echo "\t$(OK)";else echo "\t$(FAIL)"; fi
	@echo -n "4-print_most_numbers.c: "
	@betty 4-print_most_numbers.c | if [ $$? -eq 0 ]; then echo "$(OK)"; else echo "\t$(FAIL)"; fi
	@echo -n "5-more_numbers.c: "
	@betty 5-more_numbers.c | if [ $$? -eq 0 ]; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi
	@echo -n "6-print_line.c: "
	@betty 6-print_line.c | if [ $$? -eq 0 ]; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi
	@echo -n "7-print_diagonal.c: "
	@betty 7-print_diagonal.c | if [ $$? -eq 0 ]; then echo "\t$(OK)";else echo "\t$(FAIL)"; fi
	@echo -n "8-print_square.c: "
	@betty 8-print_square.c | if [ $$? -eq 0 ]; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi
	@echo -n "9-fizz_buzz.c: "
	@betty 9-fizz_buzz.c | if [ $$? -eq 0 ]; then echo "\t\t$(OK)"; else echo "\t\t$(FAIL)"; fi
	@echo -n "10-print_triangle.c: "
	@betty 10-print_triangle.c | if [ $$? -eq 0 ]; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi
	@echo -n "100-prime_factor.c: "
	@betty 100-prime_factor.c | if [ $$? -eq 0 ]; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi
	@echo -n "101-print_number.c: "
	@betty 101-print_number.c | if [ $$? -eq 0 ]; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi
	@echo "\nDone."

0:
	@$(CC) $(CFLAGS) $(TESTDIR)/0-main.c 0-isupper.c -o 0-isupper
	@printf "0-isupper: "
	@./0-isupper > 0-output
	@if cmp 0-output $(OUTPUTDIR)/0-isupper.out ; then echo "\t\t$(OK)"; else echo "\t\t$(FAIL)"; fi

1:
	@$(CC) $(CFLAGS) $(TESTDIR)/1-main.c 1-isdigit.c -o 1-isdigit
	@printf "1-isdigit: "
	@./1-isdigit > 1-output
	@if cmp 1-output $(OUTPUTDIR)/1-isdigit.out ; then echo "\t\t$(OK)"; else echo "\t\t$(FAIL)"; fi

2:
	@$(CC) $(CFLAGS) $(TESTDIR)/2-main.c 2-mul.c -o 2-mul
	@printf "2-mul: "
	@./2-mul > 2-output;
	@if  cmp 2-output $(OUTPUTDIR)/2-mul.out ; then echo "\t\t\t$(OK)"; else echo "\t\t\t$(FAIL)"; fi

3:
	@$(CC) $(CFLAGS) $(TESTDIR)/3-main.c $(TESTDIR)/_putchar.c 3-print_numbers.c -o 3-print_numbers
	@printf "3-print_numbers: "
	@./3-print_numbers > 3-output
	@if  cmp 3-output $(OUTPUTDIR)/3-print_numbers.out ; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi

4:
	@$(CC) $(CFLAGS) $(TESTDIR)/4-main.c $(TESTDIR)/_putchar.c 4-print_most_numbers.c -o 4-print_most_numbers
	@printf "4-print_most_numbers: "
	@./4-print_most_numbers > 4-output
	@if  cmp 4-output $(OUTPUTDIR)/4-print_most_numbers.out ; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi

5:
	@$(CC) $(CFLAGS) $(TESTDIR)/5-main.c $(TESTDIR)/_putchar.c 5-more_numbers.c -o 5-more_numbers
	@printf "5-more_numbers: "
	@./5-more_numbers > 5-output
	@if  cmp 5-output $(OUTPUTDIR)/5-more_numbers.out ; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi

6:
	@$(CC) $(CFLAGS) $(TESTDIR)/6-main.c $(TESTDIR)/_putchar.c 6-print_line.c -o 6-print_line
	@printf "6-print_line: "
	@./6-print_line > 6-output
	@if  cmp 6-output $(OUTPUTDIR)/6-print_line.out; then echo "\t\t$(OK)"; else echo "\t\t$(FAIL)"; fi

7:
	@$(CC) $(CFLAGS) $(TESTDIR)/7-main.c $(TESTDIR)/_putchar.c 7-print_diagonal.c -o 7-print_diagonal
	@printf "7-print_diagonal: "
	@./7-print_diagonal > 7-output
	@if  cmp 7-output $(OUTPUTDIR)/7-print_diagonal.out; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi

8:
	@$(CC) $(CFLAGS) $(TESTDIR)/8-main.c $(TESTDIR)/_putchar.c 8-print_square.c -o 8-print_square
	@printf "8-print_square: "
	@./8-print_square > 8-output
	@if  cmp 8-output $(OUTPUTDIR)/8-print_square.out ; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi

9:
	@$(CC) $(CFLAGS) 9-fizz_buzz.c -o 9-fizz_buzz
	@printf "9-fizz_buzz: "
	@./9-fizz_buzz > 9-output
	@if  cmp 9-output $(OUTPUTDIR)/9-fizz_buzz.out ; then echo "\t\t$(OK)"; else echo "\t\t$(FAIL)"; fi

10:
	@$(CC) $(CFLAGS) $(TESTDIR)/10-main.c $(TESTDIR)/_putchar.c 10-print_triangle.c -o 10-print_triangle
	@printf "10-print_triangle: "
	@./10-print_triangle > 10-output
	@if  cmp 10-output $(OUTPUTDIR)/10-print_triangle.out ; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi

100:
	@$(CC) $(CFLAGS) 100-prime_factor.c -o 100-prime_factor
	@printf "100-prime_factor: "
	@./100-prime_factor > 100-output
	@if  cmp 100-output $(OUTPUTDIR)/100-prime_factor.out ; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi

101:
	@$(CC) $(CFLAGS) 101-print_number.c $(TESTDIR)/101-main.c $(TESTDIR)/_putchar.c -o 101-print_number
	@printf "101-print_number: "
	@./101-print_number > 101-output
	@if  cmp 101-output $(OUTPUTDIR)/101-print_number.out ; then echo "\t$(OK)"; else echo "\t$(FAIL)"; fi

clean:
	@rm -f 0-isupper 1-isdigit 2-mul 3-print_numbers 4-print_most_numbers 5-more_numbers 6-print_line 7-print_diagonal 8-print_square 9-fizz_buzz 10-print_triangle 100-prime_factor 101-print_number
	@rm -f 0-output 1-output 2-output 3-output 4-output 5-output 6-output 7-output 8-output 9-output 10-output 100-output 101-output
	@echo "Cleaned up!"
