#include "Game.hpp"

Game::Game() {
}

Game::Game(int width, int height) : _width(width), _height(height) {
	this->_lib = LIBSDL2;
	this->init();
	this->running();
}

Game::Game(Game const &src) {
	*this = src;
}

Game::~Game() {

}

void	Game::init() {
	t_snake		snake_part;
	
	this->_started = false;
	this->_handle = NULL;
	this->key = 0;
	this->_eating = false;
	this->_lost = false;
	this->_direction = DIR_LEFT;
	std::srand(std::time(0));
	for (int i = 0 ; i < 3 ; i++) {
		snake_part.part_number = i;
		snake_part.x = this->_width / 2 + i;
		snake_part.y = this->_height / 2;
		snake_part.head = (i == 0) ? true : false;
		this->snake.push_back(snake_part);
	}
}

void	Game::move_snake() {
	static int	x = -1;
	static int	y = 0;
	t_snake		new_part;

	if (this->_eating) {
		new_part.x = this->snake[this->snake.size() - 1].x;
		new_part.y = this->snake[this->snake.size() - 1].y;
		new_part.part_number = this->snake.size();
		new_part.head = false;
	}

	for (unsigned long i = (this->snake.size() - 1) ; i > 0 ; i--) {
		// printf("A. i : %lu, x : %d, y : %d\n",i ,this->snake[i].x, this->snake[i].y);
		// printf("B. i : %lu, x : %d, y : %d\n",i - 1 ,this->snake[i-1].x, this->snake[i-1].y);

		this->snake[i].x = this->snake[i - 1].x;
		this->snake[i].y = this->snake[i - 1].y;
	}

	if (this->_direction == DIR_RIGHT) {
		if (this->key == RIGHT) {
			x = 0;
			y = 1;
			this->_direction = DIR_DOWN;
		}
		if (this->key == LEFT) {
			x = 0;
			y = -1;
			this->_direction = DIR_UP;
		}
	}
	else if (this->_direction == DIR_LEFT) {
		if (this->key == RIGHT) {
			x = 0;
			y = -1;
			this->_direction = DIR_UP;
		}
		if (this->key == LEFT) {
			x = 0;
			y = 1;
			this->_direction = DIR_DOWN;
		}
	}
	else if (this->_direction == DIR_UP) {
		if (this->key == RIGHT) {
			x = 1;
			y = 0;
			this->_direction = DIR_RIGHT;
		}
		if (this->key == LEFT) {
			x = -1;
			y = 0;
			this->_direction = DIR_LEFT;
		}
	}
	else if (this->_direction == DIR_DOWN) {
		if (this->key == RIGHT) {
			x = -1;
			y = 0;
			this->_direction = DIR_LEFT;
		}
		if (this->key == LEFT) {
			x = 1;
			y = 0;
			this->_direction = DIR_RIGHT;
		}		
	}
	this->snake[0].x += x;
	this->snake[0].y += y;
	
	if (this->_eating) {
		this->snake.push_back(new_part);
		this->_eating = false;
	}
	
}

void	Game::check_lose() {
	if (this->snake[0].x == this->_width || this->snake[0].y == this->_height ||
		this->snake[0].x == -1 || this->snake[0].y == -1) {
		printf("!!!! bord touche !!\n");
		this->_lost = true;
	}
	for (std::vector<t_snake>::iterator it = this->snake.begin(); it != this->snake.end(); ++it) {		
		if (it != this->snake.begin() && it->x == this->snake[0].x && it->y == this->snake[0].y) {
			printf("!!! corps touche !!!\n");
			this->_lost = true;
			break ;
		}

	}
}

void	Game::eat() {
	for (std::vector<t_food>::iterator it = this->food.begin(); it != this->food.end(); ++it) {
		if (it->x == this->snake[0].x && it->y == this->snake[0].y) {
			this->_eating = true;
			this->food.erase(it);
		}
	}
}

void	Game::add_food() {
	t_food		food;
	int			x = -1;
	int			y = -1;

	while (x < 0 && y < 0) {
		x = std::rand() % this->_width;
		y = std::rand() % this->_height;
		for (auto i : this->snake) {
			if (x == i.x && y == i.y) {
				x = -1;
				y = -1;
				break ;
			}
		}
	}
	food.x = x;
	food.y = y;
	this->food.push_back(food);
}

void	Game::handle_lib() {
	AGraph* (*start_lib)(int, int);
	
	start_lib = (AGraph*(*)(int, int))dlsym(this->_handle, "create_object");
	this->_Graphlib = (AGraph*)start_lib(this->_width, this->_height);
}

void	Game::start_lib() {
	if (this->_started == false) {
		if (this->_lib == LIBSDL2)
			this->_handle = dlopen("./libSDL2.so", RTLD_LAZY);
		else if (this->_lib == LIBNCURSES)	
			this->_handle = dlopen("./libNcurses.so", RTLD_LAZY);
		if (!this->_handle) {
			std::cerr << "dlopen erreur : " << dlerror() << std::endl;
			exit(EXIT_FAILURE);
		}
		handle_lib();
		this->_started = true;
	}
}

void	Game::end_lib() {
	void (*destroy_lib)(AGraph*);
	
	destroy_lib = (void(*)(AGraph*))dlsym(this->_handle, "destroy_object");
	destroy_lib(this->_Graphlib);
	dlclose(this->_handle);
	this->_started = false;
}

void	Game::running() {
	double		processed_time;
	bool		update;

	update = false;
	processed_time = clock();
	this->_speed = 100000 / CYCLE_PER_SEC;
	while (1) {
		this->start_lib();
		if (!this->key)
			this->key = this->_Graphlib->get_key();
		if (this->key == LIBSDL2 || this->key == LIBNCURSES)
		{
			this->_lib = this->key;
			this->end_lib();
			continue ;
		}
		if (this->key == -1)
		{
			this->end_lib();
			break ;
		}
		if (clock() > processed_time) {
			if (this->key == RIGHT)
				printf("key RIGHT\n");
			if (this->key == LEFT)
				printf("key LEFT\n");
			if (this->key == 0)
				printf("No key pressed\n");
			printf("part 0, x : %d, y : %d\n", this->snake[0].x,this->snake[0].y);
			printf("part 1, x : %d, y : %d\n", this->snake[1].x,this->snake[1].y);
			printf("part 2, x : %d, y : %d\n", this->snake[2].x,this->snake[2].y);
			printf("direction : %c\n", this->_direction);
			add_food();
			eat();
			move_snake();
			check_lose();
			processed_time += this->_speed;
			this->key = 0;
			update = true;
		}
		this->_Graphlib->update(&this->snake, &this->food, this->_speed, update);
		update = false;
		if (this->_lost)
			break ;
	}
}

Game &Game::operator=(Game const &rhs) {
	if (this != &rhs)
		*this = rhs;
	return (*this);
}
