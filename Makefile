# Created By: Achraf El Khnissi

NAME		= alx-check

CC			= c++
FLAGS		= -Wall -Wextra -Werror -std=c++17
RM			= rm -rf

OBJDIR = build

ANIMATION	= $(addprefix animation/, animation)
ANIM_HEADER	= $(addprefix animation/, animation.hpp)

CHERCKER	= $(addprefix checker/, Checker)
CHECKER_HEADER	= $(addprefix checker/, Checker.hpp)

INSTALLER	= $(addprefix installer/, Installer dependencies installMethods installerUtils)
INSTALLER_HEADER	= $(addprefix installer/, Installer.hpp)

PRINTER		= $(addprefix printer/, Printer)
PRINTER_HEADER	= $(addprefix printer/, Printer.hpp)

FILES		= $(addprefix src/, main $(CHERCKER) $(INSTALLER) $(PRINTER))

SRC			= $(FILES:=.cpp)
OBJ			= $(addprefix $(OBJDIR)/, $(FILES:=.o))

HEADER		= $(addprefix inc/, main.hpp) $(addprefix src/, $(CHECKER_HEADER) $(INSTALLER_HEADER) $(PRINTER_HEADER))
INCLUDES	= $(addprefix -I , inc $(addprefix src/, Checker Installer Printer))


#Colors:
GREEN		=	\e[92;5;118m
YELLOW		=	\e[93;5;226m
GRAY		=	\e[33;2;37m
RESET		=	\e[0m
CURSIVE		=	\e[33;3m

#Debug
ifeq ($(DEBUG), 1)
   OPTS = -g
endif

.PHONY: all clean fclean re bonus norm

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@printf "$(CURSIVE)$(GRAY) 	- Compiling $(NAME)... $(RESET)\n"
	@$(CC) $(FLAGS) $(OPTS) $(OBJ) $(INCLUDES) -o $(NAME)
	@printf "$(_SUCCESS) $(GREEN)- Executable ready.\n$(RESET)"

$(OBJDIR)/%.o: %.cpp $(HEADER)
	@mkdir -p $(dir $@)
	@ printf "$(CURSIVE)$(GRAY) 	- Making object file $@ from source file $< ... $(RESET)\n"
	@$(CC) $(FLAGS) $(OPTS) $(INCLUDES) -c $< -o $@

clean:
	@ $(RM) $(OBJDIR) $(OBJ)
	@printf "$(CURSIVE)$(GRAY)	- Removing object files ... $(RESET)\n"
	@printf "$(YELLOW)    - Object files removed.$(RESET)\n"

fclean: clean
	@ $(RM) $(NAME)
	@printf "$(CURSIVE)$(GRAY)	- Removing $(NAME)... $(RESET)\n"
	@printf "$(YELLOW)    - Executable removed.$(RESET)\n"

re: fclean all
