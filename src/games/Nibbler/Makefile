##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

NAME		=	arcade_nibbler.so

CFLAGS  	=	-I$(ITRF_DIR)	\
				-I$(CONFIG_DIR)	\

CPPFLAGS	=	-W -Wall -Wextra -Werror -shared -fPIC $(CFLAGS)
CXXFLAGS	=	-fno-gnu-unique -Ofast

CONFIG_DIR	=	$(SRC_DIR)Config/

SRC_DIR		=	../../../src/

ITRF_DIR	=	$(SRC_DIR)Interfaces/

SRCS		=	Nibbler.cpp	\

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)
	@echo "Build Nibbler ok!"

$(NAME): $(OBJS)
	@g++ -o $(NAME) $(OBJS) $(CPPFLAGS) -ldl

debug: CPPFLAGS += -g3
debug: $(NAME)
	@echo "Build Nibbler debug ok!"

clean:
	@$(RM) $(OBJS)
	@echo "Clean Nibbler ok!"

fclean: clean
	@$(RM) ../../../lib/$(NAME)
	@echo "Fclean Nibbler ok!"

re: fclean all

.PHONY: all debug clean fclean re
