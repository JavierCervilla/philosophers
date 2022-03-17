/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:19:31 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/17 10:00:17 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_check_plenty_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params[NUM_PHILOS]
		&& data->philos[i].times_eat >= data->params[NUM_TIMES_EAT])
		i++;
	if (i == data->params[NUM_PHILOS])
		data->all_eaten = 1;
}

void	ft_control_threads(t_data *data)
{
	int	i;

	while (data->all_eaten == 0)
	{
		i = -1;
		while (!data->died && ++i < data->params[NUM_PHILOS])
		{
			pthread_mutex_lock(&data->start);
			if (data->params[TIME_TO_DIE]
				< (int)( ft_get_current_time() - data->philos[i].last_eat))
			{
				print_status_change(&data->philos[i], DYING);
				data->died = 1;
			}
			pthread_mutex_unlock(&data->start);
			//usleep(100);
		}
		if (data->died == 1)
			break ;
		ft_check_plenty_philos(data);
	}
}
