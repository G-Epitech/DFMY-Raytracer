##
## EPITECH PROJECT, 2024
## { project name }
## File description:
## Makefile
##

LIB_CLCC 		= libclcc.a

$(LIB_CLCC):
	@$(MAKE) -C clcc -s
	@cp clcc/$(LIB_CLCC) .

all: $(LIB_CLCC)

clean:
	@$(MAKE) -C clcc clean -s

fclean:
	@$(MAKE) -C clcc fclean -s
	@rm -f $(LIB_CLCC)

.PHONY: $(LIB_CLCC) all clean fclean
