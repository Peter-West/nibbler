NAME		=nibbler
NAMESDL2	=libSDL2tmp.so
VERSION		=0.0.1
CFLAGS		=-Wall -Werror -Wextra -g -std=c++11
CFLAGSLIB	=-Wall -Werror -Wextra -g -fPIC -std=c++11
LFLAGSLIB	=-shared
CC 			=clang++-3.5
LIBSDL2		=`sdl2-config --libs`
LIB			=-ldl 
SRC			=main.cpp Args.cpp Game.cpp
SRCSDL2		=Sdl2.cpp
OBJ			=$(SRC:.cpp=.o)
OBJSDL2		=$(SRCSDL2:.cpp=.o)

all: $(NAMESDL2) $(NAME) finish

$(NAMESDL2):
	$(CC) $(CFLAGSLIB) -c $(SRCSDL2)
	$(CC) $(LFLAGSLIB) -o $(NAMESDL2) $(OBJSDL2) $(LIBSDL2)

$(NAME): 
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(LIB) -o $(NAME) $(OBJ)
	# $(CC)  -o $(NAME) $(OBJ) -L. -lshared

clean:
	@(rm -rf $(OBJSDL2))
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAMESDL2))
	@(rm -rf $(NAME))

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\\\\033[32m$(NAME)\\\\033[00m]")

.PHONY: all clean fclean re v