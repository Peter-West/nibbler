#ifndef GAME_HPP
# define GAME_HPP
# define CYCLE_PER_SEC	20
// # define UP				11
// # define DOWN			12
# define RIGHT			13
# define LEFT			14
# define DIR_UP			'u'
# define DIR_DOWN		'd'
# define DIR_RIGHT		'r'
# define DIR_LEFT		'l'
# define LIBSDL2		1
# define LIB2			2
# define LIB3			3
# define EXIT			-1
# include <iostream>
# include <cstdlib>
# include <stdexcept>
# include <vector>
# include <ctime>
# include "IGraph.hpp"

class Game
{
public:
	Game();
	Game(AGraph*, int, int);
	~Game();
	Game(Game const &src);
	Game &operator=(Game const &rhs);
	void					init();
	void					running(AGraph*);
	void					move_snake();
	int						key;
	std::vector<t_snake>	snake;
	std::vector<t_food>		food;

private:
	void					check_lose();
	void					add_food();
	void					eat();
	int						_width;
	int						_height;
	char					_direction;
	bool					_lost;
	bool					_eating;
};

#endif