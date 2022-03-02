/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:45:02 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/02 18:17:47 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_boolean ft_check_all_plenty(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->params[NUM_PHILOS])
	{
		if (data->philos[i].plenty == FALSE)
			return (FALSE);
	}
	return (TRUE);
}

t_boolean ft_check_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->dt->start);
	if (philo->last_eat + philo->dt->params[TIME_TO_DIE]
		< ft_get_current_time())
	{
		pthread_mutex_unlock(&philo->dt->start);
		return (TRUE);
	}
	pthread_mutex_unlock(&philo->dt->start);
	return (FALSE);
}

t_boolean ft_check_any_death(t_philo *philo)
{
	int i;

	i = -1;
	while (++i < philo->dt->params[NUM_PHILOS])
	{
		if (ft_check_death(&philo[i]))
			return (TRUE);
	}
	return (FALSE);
}

void *eat_think_sleep(void *philo_address)
{
	t_philo *philo;

	philo = (t_philo *)philo_address;
	if (!philo)
		return (NULL);
	if (philo->id % 2)
		smart_sleep(2);
	while (!ft_check_death(philo) && !ft_check_all_plenty(philo->dt))
	{
		if (!ft_check_death(philo) && !ft_check_all_plenty(philo->dt))
			eating_routine(philo);
		if (!ft_check_death(philo) && !ft_check_all_plenty(philo->dt))
			ft_sleep(philo);
		if (!ft_check_death(philo) && !ft_check_all_plenty(philo->dt))
			ft_think(philo);
	}
	return (NULL);
}

void eating_routine(t_philo *philo)
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

t_boolean ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->dt->start);
	philo->last_eat = ft_get_current_time();
	pthread_mutex_lock(&philo->dt->start);
	pthread_mutex_unlock(&philo->dt->start);
	print_status_change(philo, EATING);
	smart_sleep(philo->dt->params[TIME_TO_EAT]);
	philo->times_eat++;
	pthread_mutex_unlock(&philo->dt->start);
	if (philo->times_eat == philo->dt->params[NUM_TIMES_EAT])
		return (TRUE);
	return (FALSE);
}

void ft_drop_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	print_status_change(philo, DROPING_FORK);
}

void ft_think(t_philo *philo)
{
	print_status_change(philo, THINKING);
}

void ft_sleep(t_philo *philo)
{
	print_status_change(philo, SLEEPING);
	smart_sleep(philo->dt->params[TIME_TO_SLEEP]);
}

void take_right_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status_change(philo, TAKING_FORK);
}

void take_left_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_status_change(philo, TAKING_FORK);
}