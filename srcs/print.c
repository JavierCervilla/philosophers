/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:21:27 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/17 09:57:33 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	print_status_change(t_philo *philo, char *status)
{
	long	current_time;

	pthread_mutex_lock(&philo->dt->typing);
	current_time = ft_get_current_time();
	if (!philo->dt->died)
		printf("%lu ms %i %s",
			current_time - philo->dt->time_start, philo->id, status);
	pthread_mutex_unlock(&philo->dt->typing);
	return ;
}
