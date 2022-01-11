/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:29:56 by jcervill          #+#    #+#             */
/*   Updated: 2022/01/10 12:58:15 by jcervill         ###   ########.fr       */
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
    // MAIN LOOP

    ft_clean(&data);
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

int ft_init_data(t_data *data)
{
    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (-1);
    data->nb_philo = 0;
    data->time_to_die = 0;
    data->time_to_eat = 0;
    data->time_to_sleep = 0;
    data->nb_times_must_eat = 0;
    data->time_start = ft_get_current_time();
    printf("time_to_die:%d\n", data->time_to_die);
    printf("time_to_eat:%d\n", data->time_to_eat);
    printf("time_to_sleep:%d\n", data->time_to_sleep);
    printf("nb_times_must_eat:%d\n", data->nb_times_must_eat);
    printf("time_start:%ld\n", data->time_start);
    data->philos = NULL;
    return (0);
}

int ft_init_philosophers(t_data *data)
{
    int i;

    i = 0;
    data->philos = (t_philo **)malloc(sizeof(t_philo *) * data->nb_philo);
    if (!data->philos)
        return (-1);
    while (i < data->nb_philo)
    {
        data->philos[i] = (t_philo *)malloc(sizeof(t_philo));
        if (!data->philos[i])
            return (-1);
        data->philos[i]->id = i + 1;
        data->philos[i]->status = THINK;
        print_status_change(data->philos[i], *data);
        i++;
    }
    return (0);
}