#ifndef GAME_HPP
# define GAME_HPP
# define CYCLE_PER_SEC	5
// # define UP				11
// # define DOWN			12
# define RIGHT			13
# define LEFT			14
# define DIR_UP			'u'
# define DIR_DOWN		'd'
# define DIR_RIGHT		'r'
# define DIR_LEFT		'l'
# define LIBSDL2		1
# define LIBNCURSES		2
# define LIB3			3
# define EXIT			-1
# include <iostream>
# include <cstdlib>
# include <stdexcept>
# include <vector>
# include <ctime>
# include <dlfcn.h>
# include "IGraph.hpp"

class Game
{
public:
	Game();
	Game(int, int);
	~Game();
	Game(Game const &src);
	Game &operator=(Game const &rhs);
	void					init();
	void					running();
	void					move_snake();
	int						key;
	std::vector<t_snake>	snake;
	std::vector<t_food>		food;

private:
	void					check_lose();
	void					add_food();
	void					eat();
	void					handle_lib();
	void					start_lib();
	void					end_lib();
	int						_width;
	int						_height;
	char					_direction;
	bool					_lost;
	bool					_eating;
	int						_speed;
	int						_lib;
	bool					_started;
	void					*_handle;
	AGraph					*_Graphlib;
};

#endif