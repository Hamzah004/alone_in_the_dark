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

static void	ft_reverse(char *s, int start, int end)
{
	while (start < end)
	{
		ft_swap(&s[start], &s[end]);
		start++;
		end--;
	}
}

static int	next_permutation(char *s)
{
	int n;
	int i;
	int j;

	n = ft_strlen(s);
	if (n < 2)
		return 0;
	i = n - 2;
	while (i >= 0 && s[i] >= s[i + 1])
		i--;
	if (i < 0)
		return 1;
	j = n - 1;
	while (s[j] <= s[i])
		j--;
	ft_swap(&s[i], &s[j]);
	ft_reverse(s, i + 1, n - 1);
	return 0;
}

int	main(int argc, char **argv)
{
	char	*s;
	int	len;
	int	i;

	if (argc != 2)
		return 1;
	len = ft_strlen(argv[1]);
	if (len == 0)
		return 0;
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
	ft_putstr_nl(s);
	while (next_permutation(s))
		ft_putstr_nl(s);
	free(s);
	return 0;
}
