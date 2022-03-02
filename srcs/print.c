/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:21:27 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/02 10:29:49 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

// status: 0 = think, 1 = take_fork, 2 = eat, 3 = sleep, 4 = dead
void print_status_change(t_philo *philo, char *status)
{
	t_data	*data;
	long	current_time;

	data = (t_data *)philo->data;
	pthread_mutex_lock(&data->typing);
	current_time = ft_get_current_time();
	if (!data->died)
		printf("%lli ms %i %s\n", current_time - data->time_start, philo->id, status);
	pthread_mutex_unlock(&data->typing);
	return;
}
