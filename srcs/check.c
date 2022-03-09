/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 13:19:31 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/09 14:26:28 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_boolean	ft_check_all_eaten(t_data *data)
{
	int	i;

	i = 0;
	while (data->params[NUM_TIMES_EAT] > 0
		&& i < data->params[NUM_PHILOS]
		&& data->philos[i].times_eat >= data->params[NUM_TIMES_EAT])
		i++;
	data->all_eaten = (i == data->params[NUM_PHILOS]);
	return (data->all_eaten);
}

int	 ft_death_check(t_data *data)
{
	int			i;

	i = -1;
	while (!data->died)
	{
		i = -1;
		while (++i < data->params[NUM_PHILOS])
		{
			pthread_mutex_lock(&data->start);
			if (ft_get_current_time() > (data->philos[i].last_eat + data->params[TIME_TO_DIE]))
			{
				data->died = 1;
				print_status_change(&data->philos[i], DYING);
				pthread_detach(data->philos[i].th);
				break;
			}
			pthread_mutex_unlock(&data->start);
		}
		if (data->died)
			return data->died;
	}
	return data->died;
}

t_boolean ft_control_threads(t_data *data)
{
	while (!data->died /* && !data->all_eaten */)
	{
		if (!data->died)
			ft_death_check(data);
		/* if (!data->died && !data->all_eaten)
			ft_check_all_eaten(data); */
	}
	return (TRUE);
}