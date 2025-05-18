##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## Makefile
##

NIBBLER_DIR	=	./Nibbler/
SNAKE_DIR	=	./Snake/

all:
	@make -s -C $(NIBBLER_DIR)
	@make -s -C $(SNAKE_DIR)
	@mv $(NIBBLER_DIR)*.so ../../lib/
	@mv $(SNAKE_DIR)*.so ../../lib/
	@echo "Build game library ok!"

debug:
	@make debug -s -C $(NIBBLER_DIR)
	@make debug -s -C $(SNAKE_DIR)
	@mv $(NIBBLER_DIR)*.so ../../lib/
	@mv $(SNAKE_DIR)*.so ../../lib/
	@echo "Build debug game library ok!"

clean:
	@make clean -s -C $(NIBBLER_DIR)
	@make clean -s -C $(SNAKE_DIR)
	@echo "Clean game library ok!"

fclean: clean
	@make fclean -s -C $(NIBBLER_DIR)
	@make fclean -s -C $(SNAKE_DIR)
	@echo "Fclean game library ok!"

re: fclean all

.PHONY: all clean fclean re
