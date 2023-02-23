CC=gcc
CFLAGS=-Wall -Wextra -Werror -pedantic -std=c99 -g -O0

RED=\033[0;31m
GREEN=\033[0;32m
NC=\033[0m

OK=$(GREEN)OK$(NC)
KO=$(RED)KO$(NC)

TESTS=./tests

all:

0:
	@printf "0-preprocessor: "
	@if [ $$(wc -l < 0-preprocessor) -eq 2 ]; then printf "[$(OK)] "; else printf "[$(KO)] "; fi
	@export CFILE=$(TESTS)/0-main.c;
	@if ./0-preprocessor; then printf "[$(OK)] "; else printf "[$(KO)] "; fi
	@if [ -e ./c ]; then printf "[$(OK)] "; else printf "[$(KO)] "; fi
	@rm -f c
	@echo


clean:
	@rm 0-output
	@echo "$(GREEN)Cleaned up!$(NC)"