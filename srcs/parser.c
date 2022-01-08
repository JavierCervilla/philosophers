/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 01:00:07 by jcervill          #+#    #+#             */
/*   Updated: 2022/01/08 01:59:24 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int ft_check_arguments(int argc, char **argv)
{
    int bad_args;
    int i;
    int j;

    i = 0;
    bad_args = FALSE;
    if (argc != 6)
        bad_args = TRUE;
    while (argv[++i])
    {
        j = -1;
        while (argv[i][++j])
        {
            if (!ft_isdigit(argv[i][j]))
                bad_args = TRUE;
        }
    }
    if (bad_args)
    {
        printf("Usage: ./philosopher <number of philosophers> ");
        printf("<time to die> <time to eat> <time to sleep> ");
        printf("<number of time each philosopher will eat>\n");
        return (-1);
    }
    return (0);
}

int ft_parse_arguments(t_data *data, int argc, char **argv)
{
    int i;
    int bad_args;

    bad_args = FALSE;
    i = 1;
    while (i < argc)
    {
        if (i == 1)
        {
            data->nb_philo = ft_atoi(argv[i]);
            if (data->nb_philo < 1)
                bad_args = TRUE;
        }
        else if (i == 2)
        {
            data->time_to_die = ft_atoi(argv[i]);
            if (data->time_to_die < 1)
                bad_args = TRUE;
        }
        else if (i == 3)
        {
            data->time_to_eat = ft_atoi(argv[i]);
            if (data->time_to_eat < 1)
                bad_args = TRUE;
        }
        else if (i == 4)
        {
            data->time_to_sleep = ft_atoi(argv[i]);
            if (data->time_to_sleep < 1)
                bad_args = TRUE;
        }
        else if (i == 5)
        {
            data->nb_times_must_eat = ft_atoi(argv[i]);
            if (data->nb_times_must_eat < 1)
                bad_args = TRUE;
        }
        i++;
    }
    return (bad_args);
}