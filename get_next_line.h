/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaben-sa <yaben-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 17:33:21 by yaben-sa          #+#    #+#             */
/*   Updated: 2025/01/29 11:09:29 by yaben-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 9999
# endif

# ifndef MAX_BUFFER_SIZE
#  define MAX_BUFFER_SIZE 9999
# endif

# if BUFFER_SIZE > MAX_BUFFER_SIZE
#  undef BUFFER_SIZE
#  define BUFFER_SIZE MAX_BUFFER_SIZE
# endif

char	*get_next_line(int fd);
char	*gnl_strchr(const char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_substr(char *s, int start, int len);

#endif
