NAME		=nibbler
NAMESDL2	=libSDL2.so
NAMENCURSES	=libNcurses.so
VERSION		=0.0.1
CFLAGS		=-Wall -Werror -Wextra -g -std=c++11
CFLAGSLIB	=-Wall -Werror -Wextra -g -fPIC -std=c++11
LFLAGSLIB	=-shared
CC 			=clang++-3.5
LIBSDL2		=`sdl2-config --libs`
LIBNCURSES	=-lncurses
LIB			=-ldl 
SRC			=main.cpp Args.cpp Game.cpp
SRCSDL2		=Sdl2.cpp
SRCNCURSES	=Ncurses.cpp
OBJ			=$(SRC:.cpp=.o)
OBJSDL2		=$(SRCSDL2:.cpp=.o)
OBJNCURSES	=$(SRCNCURSES:.cpp=.o)

all: $(NAMESDL2) $(NAMENCURSES) $(NAME) finish

$(NAMESDL2):
	$(CC) $(CFLAGSLIB) -c $(SRCSDL2)
	$(CC) $(LFLAGSLIB) -o $(NAMESDL2) $(OBJSDL2) $(LIBSDL2)

$(NAMENCURSES):
	$(CC) $(CFLAGSLIB) -c $(SRCNCURSES)
	$(CC) $(LFLAGSLIB) -o $(NAMENCURSES) $(OBJNCURSES) $(LIBNCURSES)

$(NAME): 
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(LIB) -o $(NAME) $(OBJ)

clean:
	@(rm -rf $(OBJSDL2))
	@(rm -rf $(OBJNCURSES))
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAMESDL2))
	@(rm -rf $(NAMENCURSES))
	@(rm -rf $(NAME))

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\\\\033[32m$(NAME)\\\\033[00m]")

.PHONY: all clean fclean re v