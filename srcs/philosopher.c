/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:45:02 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/01 13:42:06 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	*eat_think_sleep(void *philo_address)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_address;
	data = (t_data *)philo->data;
	if (philo->id % 2)
		usleep(1000);
	while (!data->died)
	{
		// eat routine
		eating_routine(philo_address);
	}
	return (philo_address);
}


void	eating_routine(void	*philo_address)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_address;
	data = (t_data *)philo->data;
	take_right_fork(philo);
	take_left_fork(philo);
	ft_eat(philo);
	ft_drop_forks(philo, BOTH);
	ft_sleep(philo);
	ft_think(philo);
}

t_boolean ft_eat(t_philo *philo)
{
	t_data *data;

	data = (t_data *)philo->data;
	philo->last_eat = ft_get_current_time();
	philo->times_eat++;
	philo->status = EAT;
	print_status_change(philo, EATING);
	usleep((unsigned int)data->params[TIME_TO_EAT]);
	if (philo->times_eat == data->params[NUM_TIMES_EAT])
		return TRUE;
	return FALSE;
}

void ft_think(t_philo *philo)
{
	t_data *data;

	data = (t_data *)philo->data;
	philo->status = THINK;
	print_status_change(philo, THINKING);
}

void ft_sleep(t_philo *philo)
{
	t_data *data;

	data = (t_data *)philo->data;
	philo->status = SLEEP;
	print_status_change(philo, SLEEPING);
	usleep(data->params[TIME_TO_SLEEP]);
}

void ft_drop_forks(t_philo *philo, t_forks fork)
{
	t_data *data;

	data = (t_data *)philo->data;
	if (fork == LEFT || fork == BOTH)
		pthread_mutex_unlock(&data->forks[philo->l_fork]);
	if (fork == RIGHT || fork == BOTH)
		pthread_mutex_unlock(&data->forks[philo->r_fork]);
	print_status_change(philo, DROPING_FORK);
}

t_boolean ft_check_right_fork (int philo_id, t_data *data)
{
	t_philo *philo;

	philo = data->philos[philo_id];
	if (philo->has_right_fork)
		return TRUE;
	return FALSE;
}

t_boolean ft_check_left_fork (int philo_id, t_data *data)
{
	t_philo *philo;

	philo = data->philos[philo_id];
	if (philo->has_left_fork)
		return TRUE;
	return FALSE;
}

void	take_right_fork(t_philo *philo)
{
	t_data *data;

	data = (t_data *)philo->data;
	pthread_mutex_lock(&data->forks[philo->r_fork]);
	philo->has_right_fork = TRUE;
	print_status_change(philo, TAKING_FORK);
}

void	take_left_fork(t_philo *philo)
{
	t_data *data;

	data = (t_data *)philo->data;
	pthread_mutex_lock(&data->forks[philo->l_fork]);
	philo->has_left_fork = TRUE;
	print_status_change(philo, TAKING_FORK);
}