/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaben-sa <yaben-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:31:23 by yaben-sa          #+#    #+#             */
/*   Updated: 2025/01/29 11:33:18 by yaben-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	int	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

/*
** Joint s2 à la suite de s1. Libère s1. Retourne le nouveau pointeur
** ou NULL si l'allocation échoue.
*/
char	*gnl_strjoin(char *s1, char *s2)
{
	char	*dest;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	dest = malloc(sizeof(char)
			* (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!dest)
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	while (s1 && s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 && s2[j])
		dest[i++] = s2[j++];
	dest[i] = '\0';
	free(s1);
	return (dest);
}

/*
** Extrait une sous-chaîne de s, de taille len, à partir de start.
** Ne libère pas s, mais retourne NULL si malloc échoue.
*/
char	*gnl_substr(char *s, int start, int len)
{
	char	*sub;
	int		i;

	if (!s || start < 0 || len <= 0)
		return (NULL);
	if ((int)gnl_strlen(s) < start)
		return (NULL);
	sub = malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}
