##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##


NCURSES_DIR	=	./Ncurses/
SDL2_DIR	=	./Sdl2/
SFML_DIR	=	./Sfml/

all:
	@make -s -C $(NCURSES_DIR)
	@make -s -C $(SDL2_DIR)
	@make -s -C $(SFML_DIR)
	@mv $(NCURSES_DIR)*.so ../../lib/
	@mv $(SDL2_DIR)*.so ../../lib/
	@mv $(SFML_DIR)*.so ../../lib/
	@echo "Build graphic library ok!"

debug:
	@make -s debug -C $(NCURSES_DIR)
	@make -s debug -C $(SDL2_DIR)
	@make -s debug -C $(SFML_DIR)
	@mv $(NCURSES_DIR)*.so ../../lib/
	@mv $(SDL2_DIR)*.so ../../lib/
	@mv $(SFML_DIR)*.so ../../lib/
	@echo "Build debug graphic library ok!"

clean:
	@make -s clean -C $(NCURSES_DIR)
	@make -s clean -C $(SDL2_DIR)
	@make -s clean -C $(SFML_DIR)
	@echo "Clean graphic library ok!"

fclean: clean
	@make -s fclean -C $(NCURSES_DIR)
	@make -s fclean -C $(SDL2_DIR)
	@make -s fclean -C $(SFML_DIR)
	@echo "Fclean graphic library ok!"

re: fclean all

.PHONY: all clean fclean re
