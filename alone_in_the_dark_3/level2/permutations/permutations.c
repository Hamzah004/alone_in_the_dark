#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *s)
{
	int	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_swap(char *c1, char *c2)
{
	char	temp = *c1;
	*c1 = *c2;
	*c2 = temp;
}

void	print_out(char *out)
{
	int	i = 0;
	while (out[i])
	{
		write(1, &out[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

void	ft_sort(char *s)
{
	int	i,j, len;

	i = 0;
	len = ft_strlen(s);
	while (i < len - 1)
	{
		j = i + i;
		while (j < len)
		{
			if (s[i] > s[j])
				ft_swap(&s[i], &s[j]);
			j++;
		}
		i++;
	}
}
void	ft_permutate(char *s, char *out, char *used, int len, int depth)
{
	int	i;
	if (depth == len) // which is the len of the arr so this is right
	{
		out[depth] = '\0';
		print_out(out);
		return ;
	}
	i = 0;
	while (i < len)
	{
		if (!used[i])
		{
			used[i] = 1;
			out[depth] = s[i];
			ft_permutate(s, out, used, len, depth + 1);
			used[i] = 0;
		}
		i++;
	}
}
int	main(int argc, char **argv)
{
	int	i;
	int	len;
	char	*s;
	char	*used;
	char	*out;

	if (argc != 2)
		return (1);
	len = ft_strlen(argv[1]);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (1);
	i = 0;
	while (i < len)
	{
		s[i] = argv[1][i];
		i++;
	}
	s[i] = '\0';
	ft_sort(s);
	used = calloc(len, sizeof(char));
	out = malloc(sizeof(char) * (len + 1));
	if (!used || !out)
	{
		free(used);
		free(out);
		free(s);
		return (1);
	}
	ft_permutate(s, out, used, len, 0);
	free(s);
	free(out);
	free(used);
	return (0);
}
