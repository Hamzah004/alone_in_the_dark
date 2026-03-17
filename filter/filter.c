/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbani-at <hbani-at@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:02:58 by hbani-at          #+#    #+#             */
/*   Updated: 2026/03/17 12:28:11 by hbani-at         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	char	*buffer;
	int	bytes_read;

	(void) argv;
	if (argc < 2)
		return (1);
	buffer = (char *)malloc(sizeof(char) * 5000);
	bytes_read = 1;
	while (1)
	{
		bytes_read = read(0, buffer, 5000);
		if (bytes_read < 0)
			break ;
		write(1, &buffer, bytes_read - 1);
		free(buffer);
	}
	return (1);
}

// ./filter "this"
// stdin: today is this
// output: today is ****

// steps to solve:
// take input from the read infintely
// take input from the read that was stored in the buffer
// make funtion to search in the sentence was in the char array
// make a function to replace each char inside the found char array with *
