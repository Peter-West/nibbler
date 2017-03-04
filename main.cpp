#include "Game.hpp"
#include "Args.hpp"
#include <stdio.h>

int		main(int argc, char **argv) {
	// bool	started = false;
	// void	*handle = NULL;

	if (argc == 3) {
		try {
			Args a(argv);
			Game g(a.width, a.height);
/*			if (lib == 1) {
				if (started == false) {
					started = true;
					handle = dlopen("./libSDL2.so", RTLD_LAZY);
					if (!handle) {
						std::cerr << "dlopen erreur : " << dlerror() << std::endl;
						exit(EXIT_FAILURE);
					}
					handle_lib(&a, handle);
					started = false;
				}
			}
			if (lib == 2) {
				if (started == false)
				{
					started = true;
					handle = dlopen("./libNcurses.so", RTLD_LAZY);
					if (!handle) {
						std::cerr << "dlopen erreur : " << dlerror() << std::endl;
						exit(EXIT_FAILURE);
					}
					handle_lib(&a, handle);
					started = false;
				}
			}*/
		}
		catch (std::invalid_argument const & e) {
			std::cerr << "Error :" << e.what() << std::endl;
			std::cout << "usage: ./nibler [width] [height]" << std::endl;
			exit(EXIT_FAILURE);
		}
	}
	else {
		std::cout << "usage: ./nibler [width] [height]" << std::endl;
	}
	return (0);
}
