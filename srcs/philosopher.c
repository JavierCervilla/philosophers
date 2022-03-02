/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:45:02 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/02 12:54:07 by jcervill         ###   ########.fr       */
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
		usleep(100);
	while (!data->died)
		eating_routine(philo_address);
	printf("salgo de rutina\n");
	return (NULL);
}


void	eating_routine(void	*philo_address)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_address;
	data = (t_data *)philo->data;
	take_right_fork(philo_address);
	take_left_fork(philo_address);
	ft_eat(philo_address);
	ft_drop_forks(philo_address, BOTH);
	ft_sleep(philo_address);
	ft_think(philo_address);
}

t_boolean ft_eat(void	*philo_address)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_address;
	data = (t_data *)philo->data;
	philo->last_eat = ft_get_current_time();
	philo->times_eat++;
	philo->status = EAT;
	printf("time to eat: %u\n", (unsigned int)data->params[TIME_TO_EAT]);
	print_status_change(philo, EATING);
	smart_sleep((long long)data->params[TIME_TO_EAT], philo->data);
	if (philo->times_eat == data->params[NUM_TIMES_EAT])
		return TRUE;
	return FALSE;
}

void ft_think(void	*philo_address)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_address;
	data = (t_data *)philo->data;
	philo->status = THINK;
	print_status_change(philo, THINKING);
}

void ft_sleep(void	*philo_address)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_address;
	data = (t_data *)philo->data;
	philo->status = SLEEP;
	print_status_change(philo, SLEEPING);
	smart_sleep(data->params[TIME_TO_SLEEP], philo->data);
}

void ft_drop_forks(void	*philo_address, t_forks fork)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_address;
	data = (t_data *)philo->data;
	if (fork == LEFT || fork == BOTH)
	{
		print_status_change(philo, DROPING_FORK);
		pthread_mutex_unlock(&data->forks[philo->l_fork]);
	}
	if (fork == RIGHT || fork == BOTH)
	{
		print_status_change(philo, DROPING_FORK);
		pthread_mutex_unlock(&data->forks[philo->r_fork]);
	}
}

t_boolean ft_check_right_fork (void	*philo_address)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_address;
	data = (t_data *)philo->data;
	if (philo->has_right_fork)
		return TRUE;
	return FALSE;
}

t_boolean ft_check_left_fork (void	*philo_address)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_address;
	data = (t_data *)philo->data;
	if (philo->has_left_fork)
		return TRUE;
	return FALSE;
}

void	take_right_fork (void	*philo_address)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_address;
	data = (t_data *)philo->data;
	pthread_mutex_lock(&data->forks[philo->r_fork]);
	philo->has_right_fork = TRUE;
	print_status_change(philo, TAKING_FORK);
}

void	take_left_fork (void	*philo_address)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)philo_address;
	data = (t_data *)philo->data;
	pthread_mutex_lock(&data->forks[philo->l_fork]);
	philo->has_left_fork = TRUE;
	print_status_change(philo, TAKING_FORK);
}