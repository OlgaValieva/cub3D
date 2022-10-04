/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:16:33 by carys             #+#    #+#             */
/*   Updated: 2022/10/04 11:42:03 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "..cub3d.h"

char	*ft_strjoin(char *s1, char *s2, int n)
{
	char	*str;
	size_t	len1;
	size_t	len2;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = ft_strlen((char *)s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
    if(n == 0)
        free(s1);
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

    if (!s)
        return(0);
	len = 0;
	while (s[len])
	{
		len++;
	}
	return (len);
}

char	*ft_strtrim(char *s1, char *set, int flag, size_t i)
{
	size_t	j;
	size_t	len;
	char	*dst;

	if (!s1 || !set)
		return (NULL);
	while (s1[i] && ft_strchr(set, s1[i]))
		i++;
	j = ft_strlen((char *)s1);
	while (j > 0 && ft_strchr(set, s1[j - 1]))
		j--;
	if (j < i)
		len = i;
	else
		len = j - i;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	j = 0;
	while (s1[i] && j < len)
		dst[j++] = s1[i++];
	dst[j] = '\0';
	if (flag == 1)
		free(s1);
	return (dst);
}

int ft_strcmp(const char *s1, const char *s2)
{
    size_t	i;

	i = -1;
	if (!s1 && !s2)
		return (0);
	else if (!s1 || !s2)
		return (1);
	while (s1[++i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	}
	return (0);
}

int ft_gnl(char **line, int fd)
{
    int bytes_buf;
    char    buffer[2];

    bytes_buf = 0;
    *line = malloc(1);
    if (!(*line))
        return (-1);
    (*line)[0] = '\0';
    buffer[1] = '\0';
    while ((read(fd, buffer, 1)) > 0)
    {
        bytes_buf = 1;
        if(buffer[0] == '\n')
            break ;
        *line = ft_strjoin((*line), buffer, 0);
    }
    return (bytes_buf);
}