#include "Game.hpp"
#include "Args.hpp"
#include <stdio.h>

int		main(int argc, char **argv) {
	// bool	started = false;
	// void	*handle = NULL;

	if (argc == 3) {
		try {
			Args a(argv);
			Game g(a.width, a.height, argc, argv);
		}
		catch (const std::exception & e) {
			std::cerr << "Error :" << e.what() << std::endl;
			// std::cout << "usage: ./nibler [width] [height]" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	else {
		std::cout << "usage: ./nibler [width] [height]" << std::endl;
	}
	return (0);
}
