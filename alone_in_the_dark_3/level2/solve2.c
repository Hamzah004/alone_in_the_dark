#include <unistd.h>
#include <stdlib.h>

static int	ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return i;
}

static void	ft_swap(char *a, char *b)
{
	char t;

	t = *a;
	*a = *b;
	*b = t;
}

static void	ft_putstr_nl(const char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}

static void	ft_sort(char *s)
{
	int i;
	int j;
	int n;

	n = ft_strlen(s);
	i = 0;
	while (i < n - 1)
	{
		j = i + 1;
		while (j < n)
		{
			if (s[j] < s[i])
				ft_swap(&s[i], &s[j]);
			j++;
		}
		i++;
	}
}

static void	permute_rec(const char *s, char *used, char *out, int depth, int len)
{
	int i;

	if (depth == len)
	{
		out[len] = '\0';
		ft_putstr_nl(out);
		return ;
	}
	i = 0;
	while (i < len)
	{
		if (!used[i])
		{
			used[i] = 1;
			out[depth] = s[i];
			permute_rec(s, used, out, depth + 1, len);
			used[i] = 0;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	char	*s;
	char	*used;
	char	*out;
	int	len;
	int	i;

	if (argc != 2)
		return 1;
	len = ft_strlen(argv[1]);
	if (len == 0)
		return 1;
	s = (char *)malloc((size_t)len + 1);
	if (!s)
		return 1;
	i = 0;
	while (i < len)
	{
		s[i] = argv[1][i];
		i++;
	}
	s[len] = '\0';
	ft_sort(s);
	used = (char *)calloc((size_t)len, sizeof(char));
	out = (char *)malloc((size_t)len + 1);
	if (!used || !out)
	{
		free(out);
		free(used);
		free(s);
		return 1;
	}
	permute_rec(s, used, out, 0, len);
	free(out);
	free(used);
	free(s);
	return 0;
}
