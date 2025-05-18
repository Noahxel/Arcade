##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

NAME		=	arcade_sfml.so

CFLAGS  	=	-I$(ITRF_DIR)	\
				-I$(CONFIG_DIR)	\

CPPFLAGS	=	-W -Wall -Wextra -Werror -shared -fPIC $(CFLAGS)
CXXFLAGS	=	-fno-gnu-unique -Ofast

LDFLAGS		=	-lsfml-graphics -lsfml-window -lsfml-system

CONFIG_DIR	=	$(SRC_DIR)Config/

SRC_DIR		=	../../../src/

ITRF_DIR	=	$(SRC_DIR)Interfaces/

SRCS		=	Sfml.cpp	\

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)
	@echo "Build Sfml ok!"

$(NAME): $(OBJS)
	@g++ -o $(NAME) $(OBJS) $(CPPFLAGS) $(LDFLAGS) -ldl

debug: CPPFLAGS += -g3
debug: $(NAME)
	@echo "Build Sfml debug ok!"

clean:
	@$(RM) $(OBJS)
	@echo "Clean Sfml ok!"

fclean: clean
	@$(RM) ../../../lib/$(NAME)
	@echo "Fclean Sfml ok!"

re: fclean all

.PHONY: all debug clean fclean re
