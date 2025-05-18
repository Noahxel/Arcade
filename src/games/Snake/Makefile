##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

NAME		=	arcade_snake.so

CFLAGS  	=	-I$(ITRF_DIR)	\
				-I$(CONFIG_DIR)	\

CPPFLAGS	=	-W -Wall -Wextra -Werror -shared -fPIC $(CFLAGS)
CXXFLAGS	=	-fno-gnu-unique -Ofast

CONFIG_DIR	=	$(SRC_DIR)Config/

SRC_DIR		=	../../../src/

ITRF_DIR	=	$(SRC_DIR)Interfaces/

SRCS		=	Snake.cpp	\

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)
	@echo "Build Snake ok!"

$(NAME): $(OBJS)
	@g++ -o $(NAME) $(OBJS) $(CPPFLAGS) -ldl

debug: CPPFLAGS += -g3
debug: $(NAME)
	@echo "Build Snake debug ok!"

clean:
	@$(RM) $(OBJS)
	@echo "Clean Snake ok!"

fclean: clean
	@$(RM) ../../../lib/$(NAME)
	@echo "Fclean Snake ok!"

re: fclean all

.PHONY: all debug clean fclean re
