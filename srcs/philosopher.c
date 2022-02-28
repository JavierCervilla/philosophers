/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:45:02 by jcervill          #+#    #+#             */
/*   Updated: 2022/02/28 13:55:25 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void *ft_main_loop (void *args)
{
	t_data *data;
	int i;

	i = -1;
	data = (t_data *)args;
		
		
	return((void *)data);
}


t_boolean ft_eat(int philo_id, t_data *data)
{
	t_philo *philo;
		
	philo = data->philos[philo_id];
	philo->last_eat = ft_get_current_time();
	philo->times_eat++;
	philo->status = EAT;
	sleep((unsigned int)data->params[TIME_TO_EAT]);
	if (philo->times_eat == data->params[NUM_TIMES_EAT])
		return TRUE;
	print_status_change(data->philos[philo_id], *data);
	return FALSE;
}

void ft_think(int philo_id, t_data *data)
{
	t_philo *philo;

	philo = data->philos[philo_id];
	philo->status = THINK;
	print_status_change(data->philos[philo_id], *data);
}

void ft_sleep(int philo_id, t_data *data)
{
	t_philo *philo;

	philo = data->philos[philo_id];
	philo->status = SLEEP;
	print_status_change(philo, *data);
	sleep(data->params[TIME_TO_SLEEP]);
	print_status_change(data->philos[philo_id], *data);
}

void ft_drop_forks(int philo_id, t_data *data, t_forks fork)
{
	t_philo *philo;

	philo = data->philos[philo_id];
	data = (t_data *)philo->data;
	if (fork == LEFT || fork == BOTH)
		pthread_mutex_unlock(&data->forks[philo->l_fork]);
	if (fork == RIGHT || fork == BOTH)
		pthread_mutex_unlock(&data->forks[philo->r_fork]);
	print_status_change(data->philos[philo_id], *data);
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
	printf("Philo Nº%d takes right fork", philo->id);
}

void	take_left_fork(t_philo *philo)
{
	t_data *data;

	data = (t_data *)philo->data;
	pthread_mutex_lock(&data->forks[philo->l_fork]);
	philo->has_left_fork = TRUE;
	printf("Philo Nº%d takes left fork", philo->id);
}