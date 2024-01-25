##
## EPITECH PROJECT, 2023
## my_printf
## File description:
## The main Makefile of our project
##

CFLAGS = -I./include -Werror -Wpedantic -Wextra
CFLAGS += -lncurses
LFLAGS = -L./lib -lmy
TEST_FLAGS = --coverage -lcriterion -lgcov

SRC	=	src/my_sokoban.c		\
		src/player_and_boxes.c	\
		src/main.c				\
		src/fill_map_info.c		\
		src/check_end_game.c		\

OBJ	=	$(SRC:.c=.o)

NAME  = my_sokoban

all: libmy.a test

libmy.a:
	make -C ./lib/my/

libmylist.a:
	make -C ./lib/mylist/


test: $(OBJ)
	gcc $(SRC) -o  $(NAME) -g3 $(CFLAGS) $(LFLAGS)

valgrind: $(OBJ)
	@gcc $(SRC) -g3 $(CFLAGS) $(LFLAGS)
	@valgrind -s ./$(NAME)

clean:
	@rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

clean_lib:
	@make fclean -C./lib/my/
	@make fclean -C./lib/mylist/
	@make fclean -C./tests/

re:	fclean clean_lib all

unit_tests: re
	make unit_tests -C ./tests/

tests_run: re
	make -C ./tests/
	@gcovr
