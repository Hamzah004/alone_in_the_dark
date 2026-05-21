#include <stdlib.h>
#include <unistd.h>

void	put_uint(unsigned int x)
{
	char	c;

	if (x >= 10)
		put_uint(x / 10);
	c = '0' + (x % 10);
	write(1, &c, 1);
}

void	print_solution(int *board, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		put_uint((unsigned int)board[i]);
		if (i == n - 1)
			write(1, "\n", 1);
		else
			write(1, " ", 1);
		i++;
	}
}

int	conflicts(int *board, int col, int r) // board, 1, and since col is zero based that means we run at col - 1
{
	int	c;
	int	absolute_row_difference;
	int	absolute_column_difference;

	c = 0;
	while (c < col)
	{
		absolute_row_difference = board[c] - r;
		if (absolute_row_difference < 0)
			absolute_row_difference = -absolute_row_difference;
		absolute_column_difference = col - c;
		if (board[c] == r || absolute_row_difference == absolute_column_difference) // the first condition to check if there is another queen in the same row
			return (1);
		c++;
	}
	return (0);
}

void	solve(int *board, int col, int n)
{
	int	r;

	if (col == n)
	{
		print_solution(board, n);
		return ;
	}
	r = 0;
	while (r < n)
	{
		if (!conflicts(board, col, r)) // n times, and it takes the board, the col were in, and the row we are trying to place a queen in
		{
			board[col] = r;
			solve(board, col + 1, n);
		}
		r++;
	}
}

int	main(int argc, char **argv)
{
	int	n;
	int	*board;

	if (argc != 2)
		return (1);
	n = atoi(argv[1]);
	if (n <= 0)
		return (0);
	board = calloc((size_t)n, sizeof(int));
	if (!board)
		return (1);
	solve(board, 0, n);
	free(board);
	return (0);
}
