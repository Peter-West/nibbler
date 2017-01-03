#include "Args.hpp"

Args::Args(){

}

Args::Args(char **argv){
	this->handle_param(argv);
	this->width = atoi(argv[1]);
	this->height = atoi(argv[2]);
	check_max_min();
}

Args::Args(Args const & src) {
	*this = src;
}

Args & Args::operator=(Args const & rhs) {
	if (this != &rhs)
		*this = rhs;
	return (*this);
}

Args::~Args(){

}

void	Args::check_max_min() {
	if (this->width > MAX || this->height > MAX)
		throw std::invalid_argument("Width or height are too big");
	if (this->width < MIN || this->height < MIN)
		throw std::invalid_argument("Width or height are too small");
}

void	Args::handle_param(char **argv) {
	int i = 0;
	int j = 1;

	while (argv[j]) {
		i = 0;
		while (argv[j][i] != '\0') {
			if (!isdigit(argv[j][i])) {
				throw std::invalid_argument("Arguments must be digit only.");
				return ;
			}
			i++;
		}
		j++;
	}
}