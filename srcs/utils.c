/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:58:32 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/01 13:38:02 by jcervill         ###   ########.fr       */
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

long ft_get_miliseconds(struct timeval time_Stamp)
{
    return (time_Stamp.tv_sec * 1000 + time_Stamp.tv_usec / 1000);
}

long ft_get_current_time()
{
	struct timeval time_Stamp;
	pthread_mutex_t mutex;
	long time;

	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	gettimeofday(&time_Stamp, NULL);
	time = ft_get_miliseconds(time_Stamp);
	pthread_mutex_unlock(&mutex);
	return time;
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