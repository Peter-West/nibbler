#include "Xonze.hpp"


Xonze::Xonze(){

}

Xonze::Xonze(int width, int height): _width(width), _height(height){
	printf("Xonze started !\n");
	this->start();
}

Xonze::Xonze(Xonze const &src){
	*this = src;
}

Xonze::~Xonze(){

}

Xonze &Xonze::operator=(Xonze const &rhs){
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

extern "C" Xonze * create_object(int width, int height) {
	return new Xonze(width, height);
}

extern "C" void destroy_object(Xonze * object) {
	printf("Xonze QUIT !\n");
	delete object;
}

std::tuple<int, int> Xonze::get_screen_coords(double x, double y) {
	
	int x_scr = (int)(x * this->_horizontal_spacing + 50.0 + 0.5);
	int y_scr = (int)(y * this->_vertical_spacing + 50.0 + 0.5);
	return (std::make_tuple(x_scr, y_scr));
}

void	Xonze::draw_arena(){
	int			nsegments = this->_width + 1 + this->_height + 1;

	XSetForeground(this->_dis, this->_gc, this->_black.pixel);		
	XDrawSegments(this->_dis, this->_win, this->_gc, this->_segments, nsegments);
}

void	Xonze::draw_elems(std::vector<t_snake> *snake, std::vector<t_food> *food){
	std::tuple<int, int>		 	coords;
	
	XSetForeground(this->_dis, this->_gc, this->_white.pixel);
	XFillRectangles(this->_dis, this->_win, this->_gc, this->_rectangles, this->_width * this->_height);
	XSetForeground(this->_dis, this->_gc, this->_red.pixel);
	for (auto i : *food) {
		coords = get_screen_coords((double)i.x , (double)i.y);
		XFillRectangle(this->_dis, this->_win, this->_gc,
			std::get<0>(coords) + (int)(this->_horizontal_spacing / 4 + 0.5),
			std::get<1>(coords) + (int)(this->_vertical_spacing / 4 + 0.5),
			(int)this->_horizontal_spacing / 2,
			(int)this->_vertical_spacing / 2);
	}
	XSetForeground(this->_dis, this->_gc, this->_blue.pixel);
	for (auto i : *snake) {
		coords = get_screen_coords((double)i.x , (double)i.y);
		XFillRectangle(this->_dis, this->_win, this->_gc,
			std::get<0>(coords) + (int)(this->_horizontal_spacing / 4 + 0.5),
			std::get<1>(coords) + (int)(this->_vertical_spacing / 4 + 0.5),
			(int)this->_horizontal_spacing / 2,
			(int)this->_vertical_spacing / 2);
	}
}

void	Xonze::load_segs_wrects()
{
	this->_horizontal_spacing = (SCREEN_WIDTH - 100.0) / this->_width;
	this->_vertical_spacing = (SCREEN_HEIGHT - 100.0) / this->_height;
	double	i = 50.0;
	int		j = 0;
	this->_segments = new XSegment[this->_width + 1 + this->_height + 1];
	while ((int)i <= (SCREEN_WIDTH - 50) && j < this->_width + 1) {
		this->_segments[j].x1 = (int)(i + 0.5);
		this->_segments[j].y1 = 50;
		this->_segments[j].x2 = (int)(i + 0.5);
		this->_segments[j].y2 = SCREEN_WIDTH - 50.0;
		i += this->_horizontal_spacing;
		j++;
	}
	i = 50.0;
	while ((int)i <= (SCREEN_HEIGHT - 50) && j < this->_width + 1 + this->_height + 1) {
		this->_segments[j].x1 = 50;
		this->_segments[j].y1 = (int)(i + 0.5);
		this->_segments[j].x2 = SCREEN_HEIGHT - 50.0;
		this->_segments[j].y2 = (int)(i + 0.5);
		i += this->_vertical_spacing;
		j++;
	}

	this->_rectangles = new XRectangle[this->_width * this->_height];
	int								k = 0;
	int								x;
	int								y = 0;
	std::tuple<int, int>		 	coords;
	while (y < this->_height) {
		x = 0;
		while (x < this->_width) {
			coords = get_screen_coords(x ,y);
			this->_rectangles[k].x = std::get<0>(coords) + (int)(this->_horizontal_spacing / 4 + 0.5);
			this->_rectangles[k].y = std::get<1>(coords) + (int)(this->_vertical_spacing / 4 + 0.5);
			this->_rectangles[k].width = (int)this->_horizontal_spacing / 2;
			this->_rectangles[k].height = (int)this->_vertical_spacing / 2;
			x++;
			k++;
		}
		y++;
	}
}

void	Xonze::start(){
	this->_dis = XOpenDisplay((char *)0);
	if (this->_dis == NULL) {
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}

	Colormap screen_colormap = DefaultColormap(this->_dis, DefaultScreen(this->_dis));
	
	XAllocNamedColor(this->_dis, screen_colormap, "red", &this->_red, &this->_red);
	XAllocNamedColor(this->_dis, screen_colormap, "blue", &this->_blue, &this->_blue);
	XAllocNamedColor(this->_dis, screen_colormap, "yellow", &this->_yellow, &this->_yellow);
	XAllocNamedColor(this->_dis, screen_colormap, "white", &this->_white, &this->_white);
	XAllocNamedColor(this->_dis, screen_colormap, "black", &this->_black, &this->_black);

	this->_screen = DefaultScreen(this->_dis);
   	this->_win=XCreateSimpleWindow(this->_dis, DefaultRootWindow(this->_dis),
   		0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 5, this->_black.pixel, this->_white.pixel);
   	XSetStandardProperties(this->_dis, this->_win, "My Window", "HI!", None, NULL, 0, NULL);
   	XSelectInput(this->_dis, this->_win, ButtonPressMask|KeyPressMask);
    this->_gc=XCreateGC(this->_dis, this->_win, 0,0);        
	XMapWindow(this->_dis, this->_win);
	this->load_segs_wrects();
}

void	Xonze::close_x11(){
	XFreeGC(this->_dis, this->_gc);
	XDestroyWindow(this->_dis, this->_win);
	XCloseDisplay(this->_dis);	
}

int		Xonze::get_key(){
	while (XPending(this->_dis)) {
		XNextEvent(this->_dis, &this->_event);
		if (this->_event.type == KeyPress) {
			switch (this->_event.xkey.keycode) {
				case X_1:
					this->close_x11();
					return (LIBSDL2);
				case X_2:
					this->close_x11();
					return (LIBNCURSES);
				case X_3:
					this->close_x11();
					return (LIBX11);
				case X_ESC:
					this->close_x11();
					return (EXIT);
				case X_RIGHT:
					return (RIGHT);
				case X_LEFT:
					return (LEFT);
			}
		}
	}
	return (0);
}

void	Xonze::update(std::vector<t_snake>* snake, std::vector<t_food>* food, int speed, bool update) {
	(void)speed;

	if (update) {
		this->draw_arena();
		this->draw_elems(snake, food);
	}
}
