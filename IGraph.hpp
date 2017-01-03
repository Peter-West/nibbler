#ifndef IGRAPH_HPP
# define IGRAPH_HPP
# include <vector>

typedef struct	s_snake
{
	int			part_number;
	int			x;
	int			y;
	bool		head;
}				t_snake;

typedef struct	s_food
{
	int			x;
	int			y;
}				t_food;

class AGraph {
public:
	virtual int		get_key() = 0;
	virtual	void	update(std::vector<t_snake>*, std::vector<t_food>*) = 0;
	virtual	void	start() = 0;
	// virtual void	*create_object(int, int) = 0;
	// virtual void	destroy_object() = 0;
};

#endif