/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:21:27 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/09 14:07:34 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

// status: 0 = think, 1 = take_fork, 2 = eat, 3 = sleep, 4 = dead
void print_status_change(t_philo *philo, char *status)
{
	long	current_time;

	pthread_mutex_lock(&philo->dt->typing);
	current_time = ft_get_current_time();
	
	if (!philo->dt->died)
	{
		if (ft_strcmp(status, EATING) == 0)
			printf("%lli ms %i %s for %d time\n", current_time - philo->dt->time_start, philo->id, status, philo->times_eat);
		else
			printf("%lli ms %i %s\n", current_time - philo->dt->time_start, philo->id, status);
	}
	pthread_mutex_unlock(&philo->dt->typing);
	return;
}
