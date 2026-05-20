#include <stdio.h>
#include <stdlib.h>

void	print_solve(int *subset, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (i > 0)
			printf(" ");
		printf("%d",subset[i]);
		i++;
	}
	printf("\n");
}

void	solve(int *set, int *subset, int size, int n, int index, int sum, int len)
{
	if (index == size)
	{
		if (sum == n)
			print_solve(subset, len);
		return ;
	}
	solve(set, subset, size, n, index + 1, sum, len);
	subset[len] = set[index];
	solve(set, subset, size, n, index + 1, sum + set[index], len + 1);
}

int	main(int argc, char **argv)
{
	int	i;
	int	*set;
	int	*subset;
	int	size;
	int	n;

	if (argc < 3)
		return (1);
	n = atoi(argv[1]);
	size = argc - 2;
	set = malloc(sizeof(int) * (size > 0 ? size : 1));
	subset = malloc(sizeof(int) * (size > 0 ? size : 1));
	if (!set || !subset)
	{
		free(set);
		free(subset);
		return (1);
	}
	i = 0;
	while (i < size)
	{
		set[i] = atoi(argv[i + 2]);
		i++;
	}
	solve(set, subset, size, n, 0, 0, 0);
	free(set);
	free(subset);
}
