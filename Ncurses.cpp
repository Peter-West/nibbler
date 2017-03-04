#include "Ncurses.hpp"

Ncurses::Ncurses() {

}

Ncurses::Ncurses(int width, int height): _width(width), _height(height) {
	this->start();
}

Ncurses::Ncurses(Ncurses const &src) {
	*this = src;
}

Ncurses::~Ncurses() {

}

Ncurses		&Ncurses::operator=(Ncurses const &rhs) {
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

extern "C" Ncurses * create_object(int width, int height) {
	return new Ncurses(width, height);
}

extern "C" void destroy_object(Ncurses * object) {
	printf("Ncurses QUIT !\n");
	delete object;
}

void		Ncurses::start() {
	initscr();
	start_color();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	// init_color_pairs();
}

void		Ncurses::draw_arena() {
	this->box_around(0, 0, this->_width, this->_height);

}

void		Ncurses::draw_elems(std::vector<t_snake> *snake, std::vector<t_food> *food) {
	(void)snake;
	(void)food;
	// move();
}

void		Ncurses::update(std::vector<t_snake> *snake, std::vector<t_food> *food, int speed, bool update) {
	(void)update;
	(void)speed;
	// this->_speed = speed;
	// this->_update = update;
	erase();
	this->draw_arena();
	this->draw_elems(snake, food);
	refresh();
}

int			Ncurses::get_key() {
	int		key = getch();

	if (key == KEY_LEFT)
		return (LEFT);
	if (key == KEY_RIGHT)
		return (RIGHT);
	if (key == KEY_BACKSPACE)
		return (EXIT);
	return (key);
}

void		Ncurses::box_around(int y, int x, int h, int w) {
    move( y, x );
    addch (ACS_ULCORNER);   // upper left corner
    int j;
    for (j = 0;  j < w;  ++j)
        addch (ACS_HLINE);
    addch (ACS_URCORNER);   // upper right

    for( j = 0; j < h; ++j ) 
    {
            move(y + 1 + j, x);
            addch (ACS_VLINE);
            move(y + 1 + j, x + w + 1);
            addch (ACS_VLINE);
    }
    move( y+h+1,x );
    addch (ACS_LLCORNER);   // lower left corner

    for (j = 0;  j < w;  ++j)
        addch (ACS_HLINE);
    addch (ACS_LRCORNER);   // lower right
}
