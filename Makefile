##
## EPITECH PROJECT, 2024
## ratyracer
## File description:
## Makefile
##

NAME 		= raytracer
BUILD_PATH 	= build
LIB_PATH 	= lib

all:
			@cmake -S . -B build
			cmake --build $(BUILD_PATH)

clean:
			@rm -rf $(BUILD_PATH)

fclean:		clean
			@rm -f $(NAME)
			@rm -rf $(LIB_PATH)

re: 		fclean all

tests_run:
			echo "pass"

update:
			@cd shared && ./pull.sh .

.PHONY: all clean fclean re tests_run update
DEFAULT_GOAL := all
