#ifndef GNL
# define GNL

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

char    *get_next_line(int fd);
void	free_stash(void);

#endif
