##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

NAME		=	arcade_ncurses.so

CFLAGS  	=	-I$(ITRF_DIR)	\
				-I$(CONFIG_DIR)	\

CPPFLAGS	=	-W -Wall -Wextra -Werror -shared -fPIC $(CFLAGS)
CXXFLAGS	=	-fno-gnu-unique -Ofast

LDFLAGS		=	-lncurses

CONFIG_DIR	=	$(SRC_DIR)Config/

SRC_DIR		=	../../../src/

ITRF_DIR	=	$(SRC_DIR)Interfaces/

SRCS		=	Ncurses.cpp	\

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)
	@echo "Build Ncurses ok!"

$(NAME): $(OBJS)
	@g++ -o $(NAME) $(OBJS) $(CPPFLAGS) $(LDFLAGS) -ldl

debug: CPPFLAGS += -g3
debug: $(NAME)
	@echo "Build Ncurses debug ok!"

clean:
	@$(RM) $(OBJS)
	@echo "Clean Ncurses ok!"

fclean: clean
	@$(RM) ../../../lib/$(NAME)
	@echo "Fclean Ncurses ok!"

re: fclean all

.PHONY: all debug clean fclean re
