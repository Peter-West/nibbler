#include "Ncurses.hpp"

Ncurses::Ncurses() {

}

Ncurses::Ncurses(int width, int height): _width(width), _height(height) {	
	printf("**Ncurses Start !\n");
	this->start();
}

Ncurses::Ncurses(Ncurses const & src) {
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
	endwin();
	printf("Ncurses QUIT !\n");
	delete object;
}

void		Ncurses::init_color_pairs() {
	init_pair(1, COLOR_CYAN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
}

void		Ncurses::start() {
	initscr();
	start_color();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	nodelay(stdscr, TRUE);
	this->init_color_pairs();
}

void		Ncurses::draw_arena() {
	this->box_around(0, 0, this->_height, this->_width);
}

void		Ncurses::draw_elems(std::vector<t_snake> *snake, std::vector<t_food> *food) {
	(void)snake;
	(void)food;
	// move();
	for (auto i : *food) {
		move (i.y + 1, i.x + 1);
		attron(COLOR_PAIR(1));
		printw("F");
		attroff(COLOR_PAIR(1));
	}
	for (auto i : *snake) {
		move (i.y + 1, i.x + 1);
		if (i.head) {
			attron(COLOR_PAIR(2));
			printw("@");
			attroff(COLOR_PAIR(2));
		}
		else {
			attron(COLOR_PAIR(3));
			printw("o");
			attroff(COLOR_PAIR(3));
		}
	}
}

void		Ncurses::update(std::vector<t_snake> *snake, std::vector<t_food> *food, int speed, bool update) {
	(void)update;
	(void)speed;
	// this->_speed = speed;
	// this->_update = update;
	// printf("check 0\n");
	erase();
	// printf("check 1\n");
	this->draw_arena();
	this->draw_elems(snake, food);
	// printf("check 1.5\n");
	if (refresh() == ERR) { //seg fault
		printf("refresh fucked \n");
		perror("");
	}
	// printf("check 2\n");
}

int			Ncurses::get_key() {
	int		key = getch();

	// printf("check 3\n");
	if (key == -1)
		return (0);
	if (key == KEY_LEFT)
		return (LEFT);
	if (key == KEY_RIGHT)
		return (RIGHT);
	if (key == KEY_BACKSPACE)
		return (EXIT);
	if (key == 49)
		return (LIBSDL2);
	if (key == 50)
		return (LIBNCURSES);
	if (key == 51)
		return (LIBX11);
	return (key);
}

void		Ncurses::box_around(int y, int x, int h, int w) {
    int j;

    move(y, x);
    addch(ACS_ULCORNER);   // upper left corner
    for (j = 0; j < w; ++j)
        addch (ACS_HLINE);
    addch(ACS_URCORNER);   // upper right
    for(j = 0; j < h; ++j) {
            move(y + 1 + j, x);
            addch (ACS_VLINE);
            move(y + 1 + j, x + w + 1);
            addch(ACS_VLINE);
    }
    move(y + h + 1, x);
    addch(ACS_LLCORNER);   // lower left corner
    for (j = 0; j < w; ++j)
        addch(ACS_HLINE);
    addch(ACS_LRCORNER);   // lower right
}
