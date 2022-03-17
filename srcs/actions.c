/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:54:01 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/17 10:47:03 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_drop_forks(t_philo *philo)
{	
	pthread_mutex_unlock(philo->r_fork);
	pthread_mutex_unlock(philo->l_fork);
}

void	ft_think(t_philo	*philo)
{
	if (!philo->dt->died)
		print_status_change(philo, THINKING);
}

void	ft_sleep(t_philo *philo)
{
	if (!philo->dt->died)
	{
		print_status_change(philo, SLEEPING);
		smart_sleep(philo->dt->params[TIME_TO_SLEEP]);
	}
}

void	take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_status_change(philo, TAKING_FORK);
}

void	take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	print_status_change(philo, TAKING_FORK);
}
