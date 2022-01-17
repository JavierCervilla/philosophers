/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:29:56 by jcervill          #+#    #+#             */
/*   Updated: 2022/01/17 13:44:27 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int main(int argc, char **argv)
{
    t_data data;

    if (ft_check_arguments(argc, argv) == -1)
        return (-1);
    if (ft_init_data(&data) == -1)
        return (-1);
    if (ft_parse_arguments(&data, argc, argv))
        return (-1);
    
    if (ft_init_philosophers(&data) == -1)
        return (-1);
    ft_main_loop((void *)&data);
    ft_clean(&data);
}

int ft_init_data(t_data *data)
{
    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (-1);
    data->pause = FALSE;
    data->nb_philo = 0;
    data->time_to_die = 0;
    data->time_to_eat = 0;
    data->time_to_sleep = 0;
    data->nb_times_must_eat = 0;
    data->time_start = ft_get_current_time();
    data->philos = NULL;
    pthread_mutex_init(&data->start, NULL);
    pthread_mutex_lock(&data->start);
    return (0);
}

int ft_init_philosophers(t_data *data)
{
    int i;
    //t_boolean error;

    i = 0;
    data->philos = (t_philo **)malloc(sizeof(t_philo *) * data->nb_philo);
    if (!data->philos)
        return (-1);
    while (i < data->nb_philo)
    {
        printf("LLEGO");
        data->philos[i] = (t_philo *)malloc(sizeof(t_philo));
        if (!data->philos[i])
            return (-1);
        pthread_mutex_init(&data->philos[i]->right_fork, NULL);
        
        data->philos[i]->id = i + 1;
        data->philos[i]->status = THINK;
        data->philos[i]->times_eat = 0;

        pthread_create(&data->philos[i]->philo_thread, NULL, ft_main_loop, (void *)data);

        print_status_change(data->philos[i], *data);
        i++;
    }
    return (0);
}


void ft_clean(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->nb_philo)
    {
        free(data->philos[i]);
        data->philos[i] = NULL;
    }
    free(data->philos);
}