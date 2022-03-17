/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:45:02 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/17 10:51:43 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	ft_init_threads(t_data *data)
{
	int	i;

	i = -1;
	if (!data->philos)
		return (TRUE);
	data->time_start = ft_get_current_time();
	while (++i < data->params[NUM_PHILOS])
	{
		if (pthread_create(&data->philos[i].th, NULL,
				eat_think_sleep, &data->philos[i]) != 0)
			return (TRUE);
	}
	ft_control_threads(data);
	return (FALSE);
}

void	ft_fill_philo(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].dt = data;
	data->philos[i].r_fork = &data->forks[i];
	data->philos[i].last_eat = data->time_start;
	data->philos[i].plenty = 0;
	data->philos[i].times_eat = 0;
	if (i == 0)
		data->philos[i].l_fork = &data->forks[data->params[NUM_PHILOS] - 1];
	else
		data->philos[i].l_fork = &data->forks[i - 1];
}

void	*eat_think_sleep(void *philo_address)
{
	t_philo	*philo;

	philo = (t_philo *)philo_address;
	if (!philo)
		return (NULL);
	if (philo->id % 2)
		smart_sleep(2);
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
	take_right_fork(philo);
	take_left_fork(philo);
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
