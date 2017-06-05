NAME		=nibbler
NAMESDL2	=libSDL2.so
NAMENCURSES	=libNcurses.so
NAMEX11		=libX11.so
VERSION		=0.0.1
CFLAGS		=-Wall -Werror -Wextra -g -std=c++11
CFLAGSLIB	=-Wall -Werror -Wextra -g -fPIC -std=c++11
LFLAGSLIB	=-shared
CC 			=clang++-3.5
LIBSDL2		=`sdl2-config --libs`
LIBNCURSES	=-lncurses
LIBX11		=-lm -lX11
LIB			=-ldl 
SRC			=main.cpp Args.cpp Game.cpp
SRCSDL2		=Sdl2.cpp
SRCNCURSES	=Ncurses.cpp
SRCX11		=Xonze.cpp
OBJ			=$(SRC:.cpp=.o)
OBJSDL2		=$(SRCSDL2:.cpp=.o)
OBJNCURSES	=$(SRCNCURSES:.cpp=.o)
OBJX11		=$(SRCX11:.cpp=.o)

all: $(NAMESDL2) $(NAMENCURSES) $(NAMEX11) $(NAME) finish

$(NAMESDL2):
	$(CC) $(CFLAGSLIB) -c $(SRCSDL2)
	$(CC) $(LFLAGSLIB) -o $(NAMESDL2) $(OBJSDL2) $(LIBSDL2)

$(NAMENCURSES):
	$(CC) $(CFLAGSLIB) -c $(SRCNCURSES)
	$(CC) $(LFLAGSLIB) -o $(NAMENCURSES) $(OBJNCURSES) $(LIBNCURSES)

$(NAMEX11):
	$(CC) $(CFLAGSLIB) -c $(SRCX11)
	$(CC) $(LFLAGSLIB) -o $(NAMEX11) $(OBJX11) $(LIBX11)

$(NAME): 
	$(CC) $(CFLAGS) -c $(SRC)
	$(CC) $(LIB) -o $(NAME) $(OBJ)

clean:
	@(rm -rf $(OBJSDL2))
	@(rm -rf $(OBJNCURSES))
	@(rm -rf $(OBJX11))
	@(rm -rf $(OBJ))

fclean: clean
	@(rm -rf $(NAMESDL2))
	@(rm -rf $(NAMENCURSES))
	@(rm -rf $(NAMEX11))
	@(rm -rf $(NAME))

re: fclean all

v:
	@(echo "version: $(VERSION)")

finish:
	@(echo "[\\\\033[32m$(NAME)\\\\033[00m]")

.PHONY: all clean fclean re v