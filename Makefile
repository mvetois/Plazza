##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## compile
##

ECHO		=	/bin/echo -e
DEFAULT		=	"\e[0m"
BOLD_T		=	"\e[1m"
DIM_T		=	"\e[2m"
UNDLN_T		=	"\e[4m"
BLACK_C		=	"\e[30m"
RED_C		=	"\e[31m"
GREEN_C		=	"\e[32m"
YELLO_C		=	"\e[33m"
BLUE_C		=	"\e[34m"
MAGEN_C		=	"\e[35m"
CYAN_C		=	"\e[36m"
WHITE_C		=	"\e[97m"
DEFAULT_C	=	"\e[39m"
LIGHT_GREY	=	"\e[37m"
DARK_GREY	=	"\e[90m"
LIGHT_RED	=	"\e[91m"
LIGHT_GREEN	=	"\e[92m"
LIGHT_YELLO	=	"\e[93m"
LIGHT_BLUE	=	"\e[94m"
LIGHT_MAGEN	=	"\e[95m"
LIGHT_CYAN	=	"\e[96m"
LINE_RETURN	=	$(ECHO) ""

NAME		=	plazza
COLOR_THEME	=	$(WHITE_C)

SRC_PATH	=	src/
INCL_PATH	=	include/
PARS_PATH	=	parsing/
CMD_PATH	=	cmd/
RCPT_PATH	=	reception/
TOOL_PATH	=	tools/
KTCH_PATH	=	kitchen/
COOK_PATH	=	cooks/
PIZZA_PATH	=	pizza/

SRC			=	$(PARS_PATH)Error.cpp	\
				$(PARS_PATH)Parsing.cpp	\
				$(CMD_PATH)Cmd.cpp 		\
				$(RCPT_PATH)Reception.cpp	\
				$(KTCH_PATH)Kitchen.cpp	\
				$(KTCH_PATH)Factory.cpp	\
				$(TOOL_PATH)Mutex.cpp	\
				$(TOOL_PATH)Thread.cpp	\
				$(TOOL_PATH)ThreadPool.cpp	\
				$(TOOL_PATH)Process.cpp	\
				$(TOOL_PATH)Pipe.cpp	\
				$(PIZZA_PATH)Pizza.cpp	\
				$(TOOL_PATH)ScopedLock.cpp	\
				$(TOOL_PATH)Log.cpp	\
				$(COOK_PATH)Cooks.cpp	\
				$(PIZZA_PATH)Regina.cpp	\
				$(PIZZA_PATH)Margarita.cpp	\
				$(PIZZA_PATH)Americana.cpp	\
				$(PIZZA_PATH)Fantasia.cpp	\
				main.cpp

SRCS		=	$(SRC:%=$(SRC_PATH)/%)
OBJ			=	$(SRCS:.cpp=.o)


CC			= g++
CFLAGS		= -ldl -pthread -I $(INCL_PATH)\

DEBUG_FLAGS	=	-g3 -gdwarf-4
MAKE_RULE	=	all
CLEAN_RULE	=	clean

all:	message $(NAME)

message:
	@$(LINE_RETURN)
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)" [BUILD] : $(NAME)"$(DEFAULT)
	@$(LINE_RETURN)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(OBJ_MAIN) $(CFLAGS) && \
		$(ECHO) $(BOLD_T)$(GREEN_C)"\n[✔] COMPILED:" $(DEFAULT)$(LIGHT_GREEN) "$(NAME)\n"$(DEFAULT) || \
		$(ECHO) $(RED_C)$(BOLD_T)"[✘] "$(UNDLN_T)"BUILD FAILED:" $(LIGHT_RED) "$(NAME)\n"$(DEFAULT)

clean:
	@$(RM) $(OBJ)
	@$(RM) $(OBJ_MAIN)
	@$(RM) $(OBJ_TEST)
	@$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) \
		$(RED_C)$(BOLD_T)"DELETED: "$(DEFAULT) \
		$(LIGHT_RED)"$(NAME)'s object files"$(DEFAULT)
	@$(RM) vgcore.*
	@$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) \
		$(RED_C)$(BOLD_T)"DELETED: "$(DEFAULT) \
		$(LIGHT_RED)"Valgrind files"$(DEFAULT)
	@$(RM) src/tools/*.gcno
	@$(RM) src/tools/*.gcda
	@$(RM) src/pizza/*.gcno
	@$(RM) src/pizza/*.gcda
	@$(RM) src/parsing/*.gcno
	@$(RM) src/parsing/*.gcda
	@$(RM) tests/*.gcno
	@$(RM) tests/*.gcda
	@$(RM) tests/*.o
	@$(RM) unit_tests
	@$(ECHO) $(RED_C)$(DIM_T)"[clean]  "$(DEFAULT) \
		$(RED_C)$(BOLD_T)"DELETED: "$(DEFAULT) \
		$(LIGHT_RED)"Tests files"$(DEFAULT)

fclean: CLEAN_RULE=fclean
fclean:	clean
	@$(RM) $(NAME)
	@$(RM) unit_tests
	@$(ECHO) $(RED_C)$(DIM_T)"[fclean] "$(DEFAULT) \
		$(RED_C)$(BOLD_T)"DELETED: "$(DEFAULT) \
		$(LIGHT_RED)"Binary $(NAME)"$(DEFAULT)

re:		fclean all

debug: CFLAGS += $(DEBUG_FLAGS)
debug: COLOR_THEME = $(CYAN_C)
debug: MAKE_RULE = debug
debug: re
	@$(ECHO) $(BOLD_T)$(COLOR_THEME)"⚠ DEBUG MODE ACTIVATED ⚠\n"$(DEFAULT)

%.o: %.cpp
	@$(CC) -c $(CFLAGS) -o $@ $< && \
		$(ECHO) $(DIM_T) "cc $(CFLAGS) -c "$<$(COLOR_THEME)$(BOLD_T)" -o "$@ $(DEFAULT) || \
		$(ECHO) "\n"$(MAGEN_C) $(UNDLN_T)$(BOLD_T)"cc $(CFLAGS) -c "$<" -o "$@$(DEFAULT)"\n"

message_tests:
	@$(LINE_RETURN)
	@$(ECHO) $(BOLD_T)$(LIGHT_MAGEN)"  _______        _       "$(DEFAULT)
	@$(ECHO) $(BOLD_T)$(LIGHT_MAGEN)" |__   __|      | |      "$(DEFAULT)
	@$(ECHO) $(BOLD_T)$(LIGHT_MAGEN)"    | | ___  ___| |_ ___ "$(DEFAULT)
	@$(ECHO) $(BOLD_T)$(LIGHT_MAGEN)"    | |/ _ \/ __| __/ __|"$(DEFAULT)
	@$(ECHO) $(BOLD_T)$(LIGHT_MAGEN)"    | |  __/\__ \ |_\__ \""$(DEFAULT)
	@$(ECHO) $(BOLD_T)$(LIGHT_MAGEN)"    |_|\___||___/\__|___/"$(DEFAULT)
	@$(LINE_RETURN)

OBJ_T =	src/tools/Log.o	\
		src/pizza/Pizza.o	\
		src/pizza/Americana.o	\
		src/pizza/Fantasia.o	\
		src/pizza/Margarita.o	\
		src/pizza/Regina.o	\
		src/parsing/Error.o

OBJ_TESTS =	tests/log.o	\
			tests/pizza.o	\
			tests/error.o

tests_run: clean message_tests
		@g++ -c -o tests/log.o tests/log.cpp $(CFLAGS) -lcriterion --coverage
		@g++ -c -o tests/pizza.o tests/pizza.cpp $(CFLAGS) -lcriterion --coverage
		@g++ -c -o tests/error.o tests/error.cpp $(CFLAGS) -lcriterion --coverage
		@g++ -c -o src/tools/Log.o src/tools/Log.cpp $(CFLAGS) -lcriterion --coverage
		@g++ -c -o src/pizza/Pizza.o src/pizza/Pizza.cpp $(CFLAGS) -lcriterion --coverage
		@g++ -c -o src/pizza/Americana.o src/pizza/Americana.cpp $(CFLAGS) -lcriterion --coverage
		@g++ -c -o src/pizza/Fantasia.o src/pizza/Fantasia.cpp $(CFLAGS) -lcriterion --coverage
		@g++ -c -o src/pizza/Margarita.o src/pizza/Margarita.cpp $(CFLAGS) -lcriterion --coverage
		@g++ -c -o src/pizza/Regina.o src/pizza/Regina.cpp $(CFLAGS) -lcriterion --coverage
		@g++ -c -o src/parsing/Error.o src/parsing/Error.cpp $(CFLAGS) -lcriterion --coverage
		@$(CC) -o unit_tests $(OBJ_T) $(OBJ_TESTS) -lcriterion --coverage
		@./unit_tests
		gcovr --exclude tests/

.PHONY: all message clean fclean re debug
