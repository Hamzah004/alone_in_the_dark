#include "get_next_line.h"

int	ft_strchr(char *stash, char c)
{
	int	i;

	if (!stash)
		return (0);
	i = 0;
	while (stash[i])
	{
		if (stash[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strlen(char *stash)
{
	int	i;

	if (!stash)
		return (-1);
	i = 0;
	while (stash[i])
		i++;
	return (i);
}


char	*ft_strdup(char *stash)
{
	char	*dup;
	int	i;

	dup = malloc(sizeof(char) * (ft_strlen(stash) + 1));
	if (!dup)
		return (dup);
	i = 0;
	while (stash[i])
	{
		dup[i] = stash[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}


char	*ft_strjoin(char *stash, char *buffer)
{
	char	*result;
	int	i;
	int	j;

	if (!stash || !buffer)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(stash) + ft_strlen(buffer) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (stash[i])
	{
		result[i] = stash[i];
		i++;
	}
	j = 0;
	while (buffer[j])
	{
		result[i] = buffer[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin_free(char *stash, char *buffer)
{
	char	*result;

	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	result = ft_strjoin(stash, buffer);
	free(stash);
	return (result);
}


char	*read_file(int fd, char *stash, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && (!stash || !ft_strchr(stash, '\n')))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		buffer[bytes_read] = '\0';
		stash = ft_strjoin_free(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

char	*get_line(char *stash)
{
	char	*line;
	int	i;
	int	j;

	if (!stash || !*stash)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_stash(char *stash)
{
	char	*new_stash;
	int	i;
	int	j;
	int	len;

	if (!stash)
		return (NULL);
	i = 0;
	while (stash[i] != '\n' && stash[i] != '\0')
		i++;
	if (stash[i] == '\n')
		i++;
	len = ft_strlen(stash) - i;
	new_stash = malloc(sizeof(char) * (len + 1));
	if (!new_stash)
		return (NULL);
	j = 0;
	while (j < len)
	{
		new_stash[j] = stash[j + i];
		j++;
	}
	new_stash[len] = '\0';
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char	*buffer;
	char	*line;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);

	buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stash = read_file(fd, stash, buffer);
	if (!stash)
		{
			free(buffer);
			return (NULL);
		}
	free(buffer);
	line = get_line(stash);
	stash = update_stash(stash);
	return (line);
}
