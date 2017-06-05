#ifndef NCURSES_HPP
# define NCURSES_HPP
# include <stdlib.h>
# include <ncurses.h>
# include <vector>
# include "IGraph.hpp"
# include "Game.hpp"

class Ncurses: public AGraph {
public:
	Ncurses();
	Ncurses(int width, int height);
	virtual ~Ncurses();
	Ncurses(Ncurses const &src);
	Ncurses &operator=(Ncurses const &rhs);
	virtual void	start();
	virtual void	update(std::vector<t_snake>*, std::vector<t_food>*, int speed, bool update);
	virtual int						get_key();

private:
	void							draw_arena();
	void							draw_elems(std::vector<t_snake> *snake, std::vector<t_food> *food);
	void							box_around(int y, int x, int h, int w);
	void							init_color_pairs();

	int								_width;
	int								_height;
};

#endif