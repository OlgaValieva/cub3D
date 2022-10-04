/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: carys <carys@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 11:12:28 by carys             #+#    #+#             */
/*   Updated: 2022/10/04 11:40:16 by carys            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "..cub3d.h"

int	ft_atoi(const char *str)
{
	long int	n;
	long int	nn;
	int			m;
	int			i;

	n = 0;
	m = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			m = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		nn = n;
		n = n * 10 + (str[i++] - '0');
		if ((nn < 0 && n > 0) || (nn > 0 && n < 0))
			return ((m == 1) * (-1));
	}	
	return (n * m);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

bool    ft_isspace(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (true);
	return (false);
}

void	ft_putstr_fd(char *s, int fd)
{
    int i;

    i = ft_strlen(s);
    if(s)
        write(fd, s, i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}
