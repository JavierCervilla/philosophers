/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:19:31 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/11 14:03:53 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_check_plenty(t_data *data)
{
	int i;
	i = -1;
	while(++i < data->params[NUM_PHILOS])
	{
		if (data->philos[i].times_eat < data->params[NUM_TIMES_EAT])
			break ;
	}
	printf("I: %d NUM_TIMES_TO_EAT: %d\n", i, data->params[NUM_TIMES_EAT] );
	if(i == data->params[NUM_PHILOS])
	{
		data->all_eaten = 1;
		write(1, "All philos has eaten enough\n", strlen("All philos has eaten enough\n"));
	}
}

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
		}
		if (data->died == 1)
			break;
		ft_check_plenty(data);
	}
}