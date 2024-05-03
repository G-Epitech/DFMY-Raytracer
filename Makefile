##
## EPITECH PROJECT, 2024
## ratyracer
## File description:
## Makefile
##

NAME 		= raytracer
TESTS_NAME 	= raytracer_tests
PLUGINS_NAMES = sphere
PLUGINS 	= $(addsuffix .so, $(addprefix plugins/raytracer_, $(PLUGINS_NAMES)))
BUILD_PATH 	= build
LIB_PATH 	= lib
COVERAGE_IGNORE_TARGETS = 	tests \
							cmake-build-debug-coverage
COVERAGE_IGNORE = $(addprefix -e , $(COVERAGE_IGNORE_TARGETS))

ifdef DEBUG
	CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Debug
else
	CMAKE_FLAGS = -DCMAKE_BUILD_TYPE=Release
endif

all:		$(NAME) $(PLUGINS)

$(NAME):
			@cmake -S . -B $(BUILD_PATH) $(CMAKE_FLAGS)
			@cmake --build $(BUILD_PATH) --target $(NAME)

plugins/%.so:
			@cmake -S . -B $(BUILD_PATH) $(CMAKE_FLAGS)
			@cmake --build $(BUILD_PATH) --target $*

clean:
			@rm -rf $(BUILD_PATH)

fclean:		clean
			@rm -f $(NAME)
			@rm -rf $(LIB_PATH)
			@rm -f $(TESTS_NAME)
			@rm -f $(PLUGINS)

re:
			@$(MAKE) fclean
			@$(MAKE) all

tests_run:
			@cmake -S . -B $(BUILD_PATH) -DCOVERAGE=ON
			@cmake --build $(BUILD_PATH) --target $(TESTS_NAME)
			@./$(TESTS_NAME) --gtest_brief=1

coverage:
			@gcovr $(COVERAGE_IGNORE)

coverage-branch:
			@gcovr $(COVERAGE_IGNORE) --branch

.PHONY: all clean fclean re tests_run update coverage coverage-branch
DEFAULT_GOAL := all
