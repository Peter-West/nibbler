#include "Game.hpp"
#include "Args.hpp"
#include <dlfcn.h>
#include <stdio.h>
// #include "Sdl2.hpp"

// typedef void*(*Sdl2_type)();
// Sdl2_type Sdl2;

// SDL_Renderer* (*rend)(SDL_Window*, int, uint);
// rend = (SDL_Renderer* (*)(SDL_Window*, int, uint))dlsym(this->handle, "SDL_CreateRenderer");
	
int main (int argc, char **argv) {
	int		lib = 1;
	bool	started = false;
	void	*handle = NULL;

	if (argc == 3) {
		try {
			Args a(argv);
			
			if (lib == 1) {
				
				if (started == false) {
					// USED LIBRARY
					started = true;
					handle = dlopen("./libSDL2tmp.so", RTLD_LAZY);
					if (!handle) {
						std::cerr << "dlopen erreur : " << dlerror() << std::endl;
						exit(EXIT_FAILURE);
					}
					// !

					// Start Lib
					AGraph* (*start_lib)(int, int);
					void (*destroy_lib)(AGraph*);

					start_lib = (AGraph*(*)(int, int))dlsym(handle, "create_object");
					destroy_lib = (void(*)(AGraph*))dlsym(handle, "destroy_object");
					
					AGraph* Graphlib = (AGraph*)start_lib(a.width, a.height);

					Game g(Graphlib, a.width, a.height);

					destroy_lib(Graphlib);
					
					dlclose(handle);
					// Closed Lib

					/*
					Sdl2* (*start_lib)(int, int);
					void (*destroy_lib)(Sdl2*);

					start_lib = (Sdl2*(*)(int, int))dlsym(handle, "create_object");
					destroy_lib = (void(*)(Sdl2*))dlsym(handle, "destroy_object");
					
					Sdl2* classSdl2 = (Sdl2*)start_lib(a.width, a.height);
					started = true;

					Game g(classSdl2);

					destroy_lib(classSdl2);
					*/
				}
			}
		}
		catch (std::invalid_argument const & e) {
			std::cerr << "Error :" << e.what() << std::endl;
			std::cout << "usage: ./nibler [width] [height]" << std::endl;
			exit(EXIT_FAILURE);
		}
		// std::cout << "et toi et moi !" << std::endl;
	}
	else {
		std::cout << "usage: ./nibler [width] [height]" << std::endl;
	}
	return (0);
}