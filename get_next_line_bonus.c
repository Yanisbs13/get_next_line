/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaben-sa <yaben-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:33:03 by yaben-sa          #+#    #+#             */
/*   Updated: 2025/01/29 11:35:01 by yaben-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*stash[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash[fd - 2] = read_and_stash(fd, stash[fd - 2]);
	if (!stash[fd - 2])
		return (NULL);
	line = extract_line(stash[fd - 2]);
	if (!line)
	{
		free(stash[fd - 2]);
		stash[fd - 2] = NULL;
		return (NULL);
	}
	stash[fd - 2] = trim_stash(stash[fd - 2]);
	return (line);
}
