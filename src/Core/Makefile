##
## EPITECH PROJECT, 2023
## Arkad
## File description:
## Makefile
##

SRC           = Core.cpp 									\
				../main.cpp									\

OBJ           = $(SRC:.cpp=.o)

NAME          = arcade

NAME_UNIT_TESTS = unit_tests

CC            = g++

CPPFLAGS      += -I ./includes
CXXFLAGS		=	-fno-gnu-unique -Ofast
CFLAGS        = -Wall -Wextra
TFLAGS        = --coverage -lcriterion

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -ldl
	mv $(NAME) ../../

tests_run:
	$(CC) $(TFLAGS) -o $(NAME_UNIT_TESTS) tests/*.cpp
	./$(NAME_UNIT_TESTS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) ../../$(NAME)
	$(RM) *.gc*

re: fclean all

.PHONY: all clean fclean re tests_run
