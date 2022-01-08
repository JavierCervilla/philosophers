/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:21:27 by jcervill          #+#    #+#             */
/*   Updated: 2022/01/08 02:11:02 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

// status: 0 = think, 1 = take_fork, 2 = eat, 3 = sleep, 4 = dead
void print_status_change(t_philo *philo, t_data *data)
{
    (void)data;

    printf("[%ld] ", ft_get_current_time());
    printf("%d ", philo->id);
    if (philo->status == THINK)
        printf("is thinking\n");
    else if (philo->status == TAKE_FORK)
        printf("has taken a fork\n");
    else if (philo->status == EAT)
        printf("is eating\n");
    else if (philo->status == SLEEP)
        printf("is sleeping\n");
    else if (philo->status == DEAD)
        printf("died\n");
}