#ifndef SDL2_HPP
# define SDL2_HPP
# define SCREEN_WIDTH	800.0
# define SCREEN_HEIGHT	800.0
# include <dlfcn.h>
# include <tuple>
# include <vector>
# include <SDL2/SDL.h>
# include "IGraph.hpp"
# include "Game.hpp"

class Sdl2 : public AGraph {
public:
	Sdl2(int, int);
	Sdl2();
	virtual ~Sdl2();
	Sdl2 &operator=(Sdl2 const & rhs);
	Sdl2(Sdl2 const & src);
	virtual void	start();
	virtual void	update(std::vector<t_snake>*, std::vector<t_food>*, int speed, bool update);

private:
	void							create_renderer();
	void							drawGrid();
	void							drawBody(std::vector<t_snake>*, std::vector<t_food>*);
	std::tuple<int, int>			get_screen_coords(double x, double y);
	void							bodyAnimation(bool, SDL_Rect);
	// void							delta();
	int								get_key();

	SDL_Renderer					*renderer;
	SDL_Window						*window;
	SDL_Event						event;
	int								_width;
	int								_height;
	double							_horizontal_spacing;
	double							_vertical_spacing;
	static std::vector<SDL_Rect>	_old_rect;
	static std::vector<SDL_Rect>	_curr_rect;
	static std::vector<SDL_Rect>	_dest_rect;
	int								_speed;
	bool							_update;
};

#endif
