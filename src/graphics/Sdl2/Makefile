##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

NAME		=	arcade_sdl2.so

CFLAGS  	=	-I$(ITRF_DIR)	\
				-I$(CONFIG_DIR)	\

CPPFLAGS	=	-W -Wall -Wextra -Werror -shared -fPIC $(CFLAGS)
CXXFLAGS	=	-fno-gnu-unique -Ofast

LDFLAGS		=	-lSDL2 -lSDL2_ttf -lSDL2_image

CONFIG_DIR	=	$(SRC_DIR)Config/

SRC_DIR		=	../../../src/

ITRF_DIR	=	$(SRC_DIR)Interfaces/

SRCS		=	Sdl2.cpp	\

OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)
	@echo "Build Sdl2 ok!"

$(NAME): $(OBJS)
	@g++ -o $(NAME) $(OBJS) $(CPPFLAGS) $(LDFLAGS) -ldl

debug: CPPFLAGS += -g3
debug: $(NAME)
	@echo "Build Sdl2 debug ok!"

clean:
	@$(RM) $(OBJS)
	@echo "Clean Sdl2 ok!"

fclean: clean
	@$(RM) ../../../lib/$(NAME)
	@echo "Fclean Sdl2 ok!"

re: fclean all

.PHONY: all debug clean fclean re
