/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:29:56 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/02 15:09:22 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (throw_in_error(ft_check_arguments(argc, argv), ERR_BAD_ARGS))
		return (STATUS_ERR);
	data = ft_init_data(data);
	if (!data)
		throw_in_error(TRUE, ERR_INIT);
	if (throw_in_error(ft_parse_arguments(data, argc - 1, argv), ERR_BAD_ARGS))
		return (STATUS_ERR);
	if (throw_in_error(ft_init_philosophers(data), ERR_INIT_PHILO))
		return (STATUS_ERR);
	if (throw_in_error(ft_init_threads(data), ERR_INIT_TH))
		return (STATUS_ERR);
/* 	while(!data->died)
		continue; */
	ft_clean(data);
	return(STATUS_NO_ERR);
}

t_data	*ft_init_data(t_data *data)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->died = FALSE;
	ft_bzero((void *)(data)->params, sizeof(data->params));
	data->time_start = ft_get_current_time();
	data->philos = NULL;
	return (data);
}

int	ft_init_threads(t_data *data)
{
	/* 	t_philo	*philos;

	philos = (t_philo *)data->philos;
	
	*/
	if (!data->philos)
		return (TRUE); 
	int		i;
	
	i = -1;
	while (++i < data->params[NUM_PHILOS])
	{
		if (pthread_create(&data->philos[i].th, NULL,
				eat_think_sleep, &data->philos[i]) != 0)
			return (TRUE);
		data->philos[i].last_eat = ft_get_current_time();
	}
	// TODO: DEATH CHECKER FOR MAIN THREAD
/* 	while(!data->died)
		continue; */
	return (FALSE);
}

int	ft_init_philosophers(t_data *data)
{
	int	i;

	i = -1;
	data->philos = malloc(sizeof(t_philo) * data->params[NUM_PHILOS]);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->params[NUM_PHILOS]);
	if (!data->philos || !data->forks)
		return (TRUE);
	while (++i < data->params[NUM_PHILOS])
		pthread_mutex_init(&data->forks[i], NULL);
	pthread_mutex_init(&data->start, NULL);
	pthread_mutex_init(&data->typing, NULL);
	i = -1;
	while (++i < data->params[NUM_PHILOS])
	{
		data->philos[i].id = i + 1;
		data->philos[i].dt = data;
		data->philos[i].has_right_fork = &data->forks[i];
		if (i == 0)
			data->philos[i].has_left_fork = &data->forks[data->params[NUM_PHILOS] - 1];
		else
			data->philos[i].has_left_fork = &data->forks[i - 1];
	}
	return (FALSE);
}


void	ft_clean(t_data *data)
{

	free(data->philos);
}