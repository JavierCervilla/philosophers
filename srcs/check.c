/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:19:31 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/16 12:10:55 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void ft_control_threads(t_data *data)
{
	int i;
	
	while (data->all_eaten == 0)
	{
		i = -1;
		while (!data->died && ++i < data->params[NUM_PHILOS])
		{
			pthread_mutex_lock(&data->start);
			if (ft_get_current_time() > data->philos[i].last_eat + data->params[TIME_TO_DIE])
			{
				print_status_change(&data->philos[i], DYING);
				data->died = 1;
			}
			pthread_mutex_unlock(&data->start);
			usleep(100);
		}
		if (data->died == 1)
			break ;
		i = 0;
		while (i < data->params[NUM_PHILOS] &&
			data->philos[i].times_eat >= data->params[NUM_TIMES_EAT])
		{
			printf("philo %d is done eating\n", i);
			i++;
		}
		if (i == data->params[NUM_PHILOS])
			break ;
	}
	printf("fuera del while\n");
}