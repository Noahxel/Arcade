##
## EPITECH PROJECT, 2023
## MAKEFILE
## File description:
## Makefile
##

NAME		=	arcade

CFLAGS  	=	-I$(CORE_DIR)	\
				-I$(ITRF_DIR)	\
				-I$(DYLOAD_DIR)	\
				-I$(CONFIG_DIR)	\

CPPFLAGS	=	-W -Wall -Wextra -Werror $(CFLAGS)
CXXFLAGS	=	-fno-gnu-unique -Ofast

SRC_DIR		=	./src/
GRAPH_DIR	=	$(SRC_DIR)graphics/
GAMES_DIR	=	$(SRC_DIR)games/

TEST_DIR	=	./tests/

CORE_DIR	=	$(SRC_DIR)Core/
CONFIG_DIR	=	$(SRC_DIR)Config/
ITRF_DIR	=	$(SRC_DIR)Interfaces/
DYLOAD_DIR	=	$(SRC_DIR)DynamicLoader/

SRCS		=	$(SRC_DIR)main.cpp			\
				$(CORE_DIR)Core.cpp			\

OBJS		=	$(SRCS:.cpp=.o)

all: core games graphicals
	@echo "Build ok!"

core:	$(NAME)

games:
	@make --no-print-directory -C $(GAMES_DIR)

graphicals:
	@make --no-print-directory -C $(GRAPH_DIR)

$(NAME): $(OBJS)
	@g++ -o $(NAME) $(OBJS) $(CPPFLAGS) -ldl

debug: CPPFLAGS += -g3
debug: all
	@make debug --no-print-directory -C $(GRAPH_DIR)
	@make debug --no-print-directory -C $(GAMES_DIR)
	@echo "Build debug ok!"

tests_run: fclean $(NAME)
	@make -C $(TEST_DIR)
	@echo "Build tests_run ok!"
	@gcovr --html --html-details -o $(TEST_DIR)cov.html
	@gcovr

clean:
	@$(RM) $(OBJS)
	@make --no-print-directory clean -C $(GRAPH_DIR)
	@make --no-print-directory clean -C $(GAMES_DIR)
	@echo "Clean ok!"

fclean: clean
	@$(RM) $(NAME)
	@make --no-print-directory fclean -C $(GRAPH_DIR)
	@make --no-print-directory fclean -C $(GAMES_DIR)
	@echo "Fclean ok!"

re: fclean all

.PHONY: all core games graphical debug tests_run clean fclean re
