#ifndef XONZE_CPP
# define XONZE_CPP
#define X_RIGHT	0x72
#define X_LEFT	0x71
#define X_1		0x57
#define X_2		0x58
#define X_3		0x59
#define X_ESC	0x09

# include "IGraph.hpp"
# include "Game.hpp"
# include <vector>
# include <tuple>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <X11/Xos.h>

class Xonze : public AGraph
{
public:
	Xonze();
	Xonze(int width, int height);
	Xonze(Xonze const &src);
	virtual ~Xonze();
	Xonze &operator=(Xonze const &rhs);
	virtual void	start();
	virtual void	update(std::vector<t_snake>*, std::vector<t_food>*, int speed, bool update);
	virtual int		get_key();
	void			close_x11();

private:
	void					draw_arena();
	void					draw_elems(std::vector<t_snake> *snake, std::vector<t_food> *food);
	std::tuple<int, int>	get_screen_coords(double x, double y);
	void					load_segs_wrects();
	// void					close_x11();
	// void					keyPressed (unsigned char key, int x, int y);
	// void					display();

	int						_width;
	int						_height;
	// int						_argc;
	// char					**_argv;

	// int						_key;
	Display					*_dis;
	int						_screen;
	Window					_win;
	GC						_gc;
	XEvent					_event;
	XSegment				*_segments;
	XRectangle				*_rectangles;
	double					_vertical_spacing;
	double					_horizontal_spacing;
	XColor					_red, _blue, _yellow, _black, _white;
};

#endif