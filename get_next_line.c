/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaben-sa <yaben-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:33:03 by yaben-sa          #+#    #+#             */
/*   Updated: 2025/01/29 11:36:41 by yaben-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
** Lit sur fd par BUFFER_SIZE octets et accumule dans stash.
** Gère le cas read() == -1 en libérant la stash pour éviter les fuites.
** Vérifie qu'on ne renvoie pas un stash=NULL par malloc échoué.
*/
static char	*read_and_stash(int fd, char *stash)
{
	char	buf[BUFFER_SIZE + 1];
	int		bytes;

	bytes = 1;
	while (!gnl_strchr(stash, '\n') && bytes != 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(stash);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		buf[bytes] = '\0';
		stash = gnl_strjoin(stash, buf);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

/*
** Retourne la ligne à extraire depuis stash (jusqu'au \n s'il existe).
** Si stash est vide ou malloc échoue, on renvoie NULL.
*/
static char	*extract_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	if (!stash || !stash[0])
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = gnl_substr(stash, 0, i);
	if (!line)
		return (NULL);
	return (line);
}

/*
** Coupe la stash pour enlever la ligne qu'on vient de prendre.
** Libère l'ancienne stash et retourne la nouvelle.
** Si pas de \n, on free et renvoie NULL.
*/
static char	*trim_stash(char *stash)
{
	char	*new_stash;
	int		i;
	int		len;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	len = 0;
	while (stash[i + len])
		len++;
	new_stash = gnl_substr(stash, i, len);
	free(stash);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_and_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = trim_stash(stash);
	return (line);
}

/*
#include <fcntl.h>      // for open()
#include <unistd.h>     // for close()
#include <stdio.h>      // for printf()
#include <stdlib.h>     // for free()
#include "get_next_line.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	int		fd3;
	char	*line;

	if (argc < 2)
	{
		printf("Usage: %s <filename>\n", argv[0]);
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	fd2 = open(argv[2], O_RDONLY);
	fd3 = open(argv[3], O_RDONLY);
	if (fd < 0)
	{
		printf("Error: could not open file '%s'\n", argv[1]);
		return (1);
	}
	line = get_next_line(fd);
	printf("GNL returned: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("GNL returned: %s", line);
	free(line);

	line = get_next_line(fd3);
	printf("GNL returned: %s", line);
	free(line);

	line = get_next_line(fd2);
	printf("GNL returned: %s", line);
	free(line);

	printf("%d, %d, %d \n", fd, fd2, fd3);

	close(fd)
	close(fd2);
	close(fd3);
	
	return (0);
}
*/