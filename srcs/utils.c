/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:58:32 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/16 12:03:50 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int ft_atoi(char *str)
{
	int sum;
	int sign;
	int found;

	sum = 0;
	sign = 1;
	found = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str && found)
	{
		if (*str >= '0' && *str <= '9')
			sum = sum * 10 + *str - '0';
		else
			found = 0;
		str++;
	}
	return (sign * sum);
}

t_boolean ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (TRUE);
	}
	return (FALSE);
}

long long diff_time (long long t1, long long t2)
{
	return (t1 - t2);
}

void	smart_sleep(int time)
{
	long long	i;

	i = ft_get_current_time();
	while (ft_get_current_time() < (i + time))
	{
		usleep(500);
	}
}

long long ft_get_current_time(void)
{
	struct timeval timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}

void	ft_bzero(void *str, size_t n)
{
	unsigned int	i;
	unsigned char	*aux;

	aux = str;
	i = 0;
	while (n-- > 0)
	{
		aux[i++] = 0;
	}
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	i = 0;
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
