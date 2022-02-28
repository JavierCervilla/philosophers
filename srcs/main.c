/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:29:56 by jcervill          #+#    #+#             */
/*   Updated: 2022/02/28 13:51:14 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (throw_in_error(ft_check_arguments(argc, argv), ERR_BAD_ARGS))
		return (-1);
	data = ft_init_data(data);
	if (!data)
		throw_in_error(TRUE, ERR_INIT);
	if (throw_in_error(ft_parse_arguments(data, argc - 1, argv), ERR_BAD_ARGS))
		return (-1);
	if (throw_in_error(ft_init_philosophers(data), ERR_INIT))
		return (-1);
	ft_main_loop((void *)data);
	ft_clean(data);
}

t_data	*ft_init_data(t_data *data)
{
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->pause = FALSE;
	ft_bzero((void *)(data)->params, sizeof(data->params));
	data->time_start = ft_get_current_time();
	data->philos = NULL;
	pthread_mutex_init(&(data)->start, NULL);
	pthread_mutex_lock(&(data)->start);
	return (data);
}

int	ft_init_philosophers(t_data *data)
{
	int	i;

	i = -1;
	data->philos = (t_philo **)malloc(sizeof(t_philo *) * data->params[NUM_PHILOS]);
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->params[NUM_PHILOS]);
	if (!data->philos)
		return (TRUE);
	while (++i < data->params[NUM_PHILOS])
	{
		data->philos[i] = (t_philo *)malloc(sizeof(t_philo));
		ft_bzero((void *)data->philos[i], sizeof(t_philo));
		if (!data->philos[i])
			return (-1);
		data->philos[i]->id = i + 1;
		data->philos[i]->data = (void *)data;
		data->philos[i]->r_fork = i;
		pthread_mutex_init(&data->forks[i], NULL);
		if (i > 0)
			data->philos[i]->l_fork = i - 1;
	}
	data->philos[0]->l_fork = i;
	return (FALSE);
}


void	ft_clean(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->params[NUM_PHILOS])
	{
		free(data->philos[i]);
		data->philos[i] = NULL;
	}
	free(data->philos);
}