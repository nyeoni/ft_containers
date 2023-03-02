# compile command
CC	=	c++

# debug flags
ifdef DEBUG
	CFLAGS	=	-std=c++98 -pedantic -g3 -fsanitize=address
else ifdef LEAKS
	CFLAGS	=	-std=c++98 -g
else ifdef FT
	CFLAGS	=	-std=c++98 -g
else ifdef STD
	CFLAGS	=	-std=c++98 -g -D STD
else
	CFLAGS	=	-std=c++98 -Wall -Wextra -Werror
endif

# exec name
ifdef FT
	NAME 	=	ft_test
else ifdef STD
	NAME 	=	std_test
else
	NAME 	=	container
endif

ifdef TEST
	SRC		=	src/test.cpp
else
	SRC		=	$(addprefix src/, main.cpp tree.cpp)
endif

INC_DIR		=	include/

OBJ			=	$(SRC:%.cpp=%.o)

%.o	:	%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@ -I$(INC_DIR)
	@echo $(BOLD)$(MINT)" Compiling with $(CC) $(CFLAGS) -c $< -o $@" ... $(RESET)
	@echo $(MAUVE) [$(notdir $^)] to [$(notdir $@)] $(RESET)

$(NAME)	:	$(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ -I$(INC_DIR)
	@echo $(L_CYAN) 🔗 Linking [$(notdir $^)] to [$@] $(RESET)
	@echo $(BOLD)$(L_PURPLE) ✨ $(NAME) ✨ $(GREEN)is ready 🎉 $(RESET)

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	@rm -f $(OBJ)
	@echo $(BOLD)$(MAUVE) 🗒 object files $(PINK)have been cleaned....🗑️$(RESET)

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)
	@rm -f ft_test
	@rm -f std_test
	@echo $(BOLD)$(L_PURPLE) ✨ $(NAME) ✨ $(PINK)have been cleaned....🗑️$(RESET)

.PHONY: re
re: fclean
	@make all
	@echo $(BOLD)$(L_PURPLE) ✨ $(NAME) ✨ $(PINK)have been rebuilt....🔄$(RESET)

.PHONY: ft
ft:
	@make TEST=1 FT=1 all
	@rm -f src/test.o

.PHONY: std
std:
	@make TEST=1 STD=1 all # test FT = 0 needed
	@rm -f src/test.o

.PHONY: debug
debug:
	@make DEBUG=1 all

.PHONY: leaks
leaks:
	@make LEAKS=1 all

######################### ASSETS #########################
GREEN="\033[32m"
MINT="\033[38;5;51m"
L_PURPLE="\033[38;5;55m"
MAUVE="\033[38;5;147m"
PINK="\033[38;5;175m"
RESET="\033[0m"
BOLD="\033[1m"
UP = "\033[A"
DOWN = "\033[B"
RIGHT = "\033[C"
LEFT = "\033[D"
CUT = "\033[K"
SAVE = "\033[s"
RESTORE = "\033[u"