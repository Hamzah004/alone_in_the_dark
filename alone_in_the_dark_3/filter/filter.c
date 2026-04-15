 #define _GNU_SOURCE
                            #include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	buffer[5000];
	char	*tmp;
	int	bytes_read;
	int	i;
	int	j;
	int	argv_len;
	int	start;


	if (argc != 2)
		return (1);
	argv_len = strlen(argv[1]);
	while ((bytes_read = read(0, buffer, sizeof(buffer))) > 0)
	{
		i = 0;
		while (i < bytes_read)
		{
			tmp = memmem(buffer + i, bytes_read - i, argv[1], argv_len);
			if (!tmp)
			{
				write(1, buffer + i, bytes_read - i);
				break ;
			}
			start = tmp - buffer;
			write(1, buffer + i, start - i);
			j = 0;
			while (j < argv_len)
			{
				write(1, "*", 1);
				j++;
			}
			i = start + argv_len;
		}
	}
	if (bytes_read < 0)
	{
		perror("Error:");
		return (1);
	}
	return (0);
}
