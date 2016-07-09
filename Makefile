
#CONFIG
	SRCS =			main.c \

	NAME =			a.out

	CC =			gcc

	EXTENTION =		c

	CFLAGS = 		-Wall -Werror -Wextra

#ADVANCED CONFIG
	SRC_PATH =		./srcs/
	INC_PATH =		./includes/
	OBJ_PATH =		./obj/
	#LIB CONFIG
		#TYPE OF BINARY: LIB or PROGRAM
		TYPE = PROGRAM
	#LIB that are make with the same makefile
		LIB_NAMES = -lesdl
		LIB_PATH =	./ESDL_Lib/
	#OTHER LIB
		LIB_SUPP = -L/usr/lib/x86_64-gnu -lSDL2
		LIB_SUPP_INC = -I/usr/include/SDL2
	#TEXT
		COMPILING_OBJECTS = "\033[4;7mCompiling Objects:\033[0m [$(NAME)]\n"
		COMPILING_BINARY = "\033[4;7mCompiling binary:\033[0m [$(NAME)]\n"
		COMPILING_DONE = "\n\033[4m\033[95md\033[93mo\033[32mn\033[96me\033[0m \033[91m!\033[0m\n\n"
		COMILING_PROGRESS = "\033[37;7m+\033[0m"
		COMPILING_CLEAN = "\033[4;7mCleaning:\033[0m [$(NAME)]\n\033[4m\033[95md\033[93mo\033[32mn\033[96me\033[0m \033[91m!\033[0m\n\n"
		COMPILING_FCLEAN = "\033[4;7mFcleaning:\033[0m [$(NAME)]\033[0m\n\033[4m\033[95md\033[93mo\033[32mn\033[96me\033[0m \033[91m!\033[0m\n\n"

#DO MAGIC
	OBJ = $(addprefix $(OBJ_PATH), $(SRCS:.$(EXTENTION)=.o))
	INC = $(addprefix -I, $(INC_PATH))
	#LIB
		LIB_INC = $(addprefix -I, $(addsuffix includes, $(LIB_PATH)))
		LIB = $(addprefix -L, $(LIB_PATH))
		INC += $(LIB_SUPP_INC)
		LDFLAGS = $(LIB) $(LIB_NAMES) $(LIB_SUPP)
		EMPTY =

all: libs name $(OBJ) done $(NAME)

$(NAME):
	@ printf $(COMPILING_BINARY)
	@ printf $(COMILING_PROGRESS)
ifeq ($(TYPE), LIB)
	@ ar -rc $(NAME) $(OBJ)
	@ ranlib $(NAME)
else
	@ $(CC) $(OBJ) $(LDFLAGS) -o $(NAME)
endif
	@ printf $(COMPILING_DONE)

$(OBJ_PATH)%.o: $(SRC_PATH)%.$(EXTENTION)
	@ printf $(COMILING_PROGRESS)
	@ mkdir -p $(OBJ_PATH) 2> /dev/null
	@ $(CC) $(INC) $(LIB_INC) -c $< -o $@

#COMPILING SUBLIBS
ifeq ($(LIB_PATH), $(EMPTY))
else
libs:
	@ $(foreach lib, $(LIB_PATH), cd $(lib) && make > /dev/null ;)
endif

clean:
	@ rm -rf $(OBJ_PATH)
	@ printf $(COMPILING_CLEAN)
#CLEANING SUBLIBS
ifeq ($(LIB_PATH), $(EMPTY))
else
	@ $(foreach lib, $(LIB_PATH), cd $(lib) && make clean > /dev/null ;)
endif

fclean: clean
	@ rm -rf $(NAME)
	@ printf $(COMPILING_FCLEAN)
#FCLEANING SUBLIBS
ifneq ($(LIB_PATH), $(EMPTY))
else
	@ $(foreach lib, $(LIB_PATH), cd $(lib) && make fclean > /dev/null ;)
endif

re: fclean all

#TEXT
name :
	@ printf $(COMPILING_OBJECTS)

done :
	@ printf $(COMPILING_DONE)

.PHONY: all clean fclean re libs