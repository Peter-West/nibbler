#ifndef ARGS_CPP
# define ARGS_CPP
# define MAX 50
# define MIN 10
# include <cstdlib>
# include <cctype>
# include <string>
# include <stdexcept>

class Args
{
public:
	Args(char **argv);
	Args(Args const & src);
	Args &operator=(Args const & rhs);
	~Args();
	int		width;
	int		height;

private:
	Args();
	void	handle_param(char **argv);
	void	check_max_min();
};

#endif