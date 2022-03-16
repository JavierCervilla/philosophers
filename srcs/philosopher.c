/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:45:02 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/16 13:55:39 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*eat_think_sleep(void *philo_address)
{
	t_philo	*philo;

	philo = (t_philo *)philo_address;
	if (!philo)
		return (NULL);
	if (philo->id % 2)
		usleep(1000);
	while (!philo->dt->died && !philo->dt->all_eaten)
	{
		if (!philo->dt->died && !philo->dt->all_eaten)
			eating_routine(philo);
		if (philo->dt->all_eaten == 1)
			break ;
		if (!philo->dt->died && !philo->dt->all_eaten)
			ft_sleep(philo);
		if (!philo->dt->died && !philo->dt->all_eaten)
			ft_think(philo);
	}
	return (NULL);
}

void	eating_routine(t_philo *philo)
{
	if (philo->id == philo->dt->params[NUM_PHILOS])
	{
		take_left_fork(philo);
		take_right_fork(philo);
	}
	else
	{
		take_right_fork(philo);
		take_left_fork(philo);
	}
	ft_eat(philo);
	ft_drop_forks(philo);
}

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->dt->start);
	print_status_change(philo, EATING);
	philo->last_eat = ft_get_current_time();
	pthread_mutex_unlock(&philo->dt->start);
	smart_sleep(philo->dt->params[TIME_TO_EAT]);
	philo->times_eat++;
	if (philo->times_eat == philo->dt->params[NUM_TIMES_EAT])
		philo->plenty = 1;
}
