#include "get_next_line_bonus.h"

int	main(int argc, char **argv)
{
	char *line;

	while (get_next_line(&line) > 0)
	{
		write(1, ">", 1);
	}
	return (0);
}
