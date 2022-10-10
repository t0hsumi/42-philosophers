#include <philosophers.h>

int	main(int argc, char **argv)
{
	t_table	table;

	if (check_args(argc, argv))
		return (1);
	if (init_table(argc, argv, &table))
		return (1);
	if (launch_simulation(&table))
		return (1);
	destroy_table(&table);
	return (0);
}
