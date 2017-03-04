#ifndef NCURSES_HPP
# define NCURSES_HPP
# include <ncurses.h>
# include <vector>
# include "IGraph.hpp"
# include "Game.hpp"

class Ncurses
{
public:
	Ncurses();
	Ncurses(int width, int height);
	virtual ~Ncurses();
	Ncurses(Ncurses const &src);
	Ncurses &operator=(Ncurses const &rhs);
	virtual void	start();
	virtual void	update(std::vector<t_snake>*, std::vector<t_food>*, int speed, bool update);

private:
	int								get_key();
	void							draw_arena();
	void							draw_elems(std::vector<t_snake> *snake, std::vector<t_food> *food);
	void							box_around(int y, int x, int h, int w);
	
	int								_width;
	int								_height;
};

#endif