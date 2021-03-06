#include "Sdl2.hpp"
#include <stdio.h>
#include <unistd.h>

Sdl2::Sdl2(int width, int height): _width(width), _height(height) {
	printf("**SDL2 Start !\n");
	this->start();
}

Sdl2::Sdl2() {

}

Sdl2::Sdl2(Sdl2 const & src){
	*this = src;
}

Sdl2::~Sdl2(){

}

extern "C" Sdl2 * create_object(int width, int height) {
	return new Sdl2(width, height);
}

extern "C" void destroy_object(Sdl2 * object) {
	atexit(SDL_Quit);
	printf("SDL QUIT !\n");
	delete object;
}

Sdl2 & Sdl2::operator=(Sdl2 const & rhs){
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

void	Sdl2::create_renderer()
{
	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (this->renderer == NULL)
		printf("Renderer could not be created ! SDL_Error : %s\n", SDL_GetError());
}

std::tuple<int, int> Sdl2::get_screen_coords(double x, double y) {
	
	int x_scr = (int)(x * this->_horizontal_spacing + 50.0 + 0.5);
	int y_scr = (int)(y * this->_vertical_spacing + 50.0 + 0.5);
	return (std::make_tuple(x_scr, y_scr));
}

void	Sdl2::bodyAnimation(bool head, SDL_Rect rect) {
	// for (auto i : this->_dest_rect) {

		if (head)
			SDL_SetRenderDrawColor(this->renderer, 125, 100, 0, 255);
		else
			SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(this->renderer, &rect);
	// }
}
/*
void	Sdl2::delta() {
	int delta_tx, delta_ty;

	delta_tx = this->_speed / this->_dest_rect[0].x - this->_old_rect[0].x;
	delta_ty = this->_speed / this->_dest_rect[0].y - this->_old_rect[0].y;
	printf("delta_ty : %d, delta_tx : %d\n", delta_tx, delta_ty);
}*/

void	Sdl2::drawBody(std::vector<t_snake> *snake, std::vector<t_food> *food) {

	SDL_Rect						rect;
	static bool						initialized = false;
	std::tuple<int, int>		 	coords;

	for (auto i : *food) {
		coords = get_screen_coords((double)i.x , (double)i.y);
		rect.x = std::get<0>(coords) + (int)(this->_horizontal_spacing / 4 + 0.5);
		rect.y = std::get<1>(coords) + (int)(this->_vertical_spacing / 4 + 0.5);
		rect.w = (int)this->_horizontal_spacing / 2;
		rect.h = (int)this->_vertical_spacing / 2;
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 255, 255);
		SDL_RenderFillRect(this->renderer, &rect);
	}

	// if (this->_update == true) {
		for (auto i : *snake) {
			coords = get_screen_coords((double)i.x , (double)i.y);
			rect.x = std::get<0>(coords) + (int)(this->_horizontal_spacing / 4 + 0.5);
			rect.y = std::get<1>(coords) + (int)(this->_vertical_spacing / 4 + 0.5);
			rect.w = (int)this->_horizontal_spacing / 2;
			rect.h = (int)this->_vertical_spacing / 2;
			// this->_dest_rect.push_back(rect);
			// if (initialized)
				this->bodyAnimation(i.head, rect);
		}
	// }
	initialized = true;
	// this->_old_rect = this->_dest_rect;
}

void	Sdl2::drawGrid() {
	double		i = 50.0;

	this->_horizontal_spacing = (SCREEN_WIDTH - 100.0) / this->_width;
	this->_vertical_spacing = (SCREEN_HEIGHT - 100.0) / this->_height;
	SDL_SetRenderDrawColor(this->renderer, 255, 255, 0, 255);
	while ((int)i <= (SCREEN_WIDTH - 50)) {
		SDL_RenderDrawLine(this->renderer, (int)(i + 0.5), 50, (int)(i + 0.5), SCREEN_WIDTH - 50.0);
		i += this->_horizontal_spacing;
	}
	i = 50.0;
	while ((int)i <= (SCREEN_HEIGHT - 50)) {
		SDL_RenderDrawLine(this->renderer, 50, (int)(i + 0.5), SCREEN_HEIGHT - 50, (int)(i + 0.5));
		i += this->_vertical_spacing;
	}
}

int		Sdl2::get_key() {
	SDL_PollEvent(&this->event);	
	if (this->event.type == SDL_KEYDOWN && this->event.key.keysym.sym == SDLK_3)
		return (LIBX11);
	if (this->event.type == SDL_KEYDOWN && this->event.key.keysym.sym == SDLK_2)
		return (LIBNCURSES);
	if (this->event.type == SDL_KEYDOWN && this->event.key.keysym.sym == SDLK_1)
		return (LIBSDL2);
	if (this->event.type == SDL_KEYDOWN && this->event.key.keysym.sym == SDLK_LEFT)
		return (LEFT);
	if (this->event.type == SDL_KEYDOWN && this->event.key.keysym.sym == SDLK_RIGHT)
		return (RIGHT);
	if (this->event.type == SDL_KEYDOWN && this->event.key.keysym.sym == SDLK_ESCAPE) {
		return (EXIT);
	}
	return (0);
}

void		Sdl2::update(std::vector<t_snake> *snake, std::vector<t_food> *food, int speed, bool update) {
	this->_speed = speed;
	this->_update = update;
	SDL_RenderClear(this->renderer);
	this->drawGrid();
	this->drawBody(snake, food);
	SDL_RenderPresent(this->renderer);
	SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
}

void		Sdl2::start() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("Sdl init Failed !\n");
	else
	{
		// CreateWindow = (SDL_Window*(*)(const char*,int,int,int,int,uint))dlsym(this->handle, "SDL_CreateWindow");
		this->window = SDL_CreateWindow("Yop Yop, c'est la SDL 2 !", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
		if (this->window == NULL)
			 printf("Window could not be created!\n");
		else
		{
			this->create_renderer();
		}
	}
}
