/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 00:21:27 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/16 11:36:31 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	ft_putchar(char c) {
	write(1, &c, 1);
}

void	ft_putnbr(int nb) {
	if (nb < 0) {
		ft_putchar('-');
		nb = -nb;
	}
	if (nb >= 10) {
		ft_putnbr(nb / 10);
		nb = nb % 10;
	}
	if (nb < 10) ft_putchar(nb + 48);
}

// status: 0 = think, 1 = take_fork, 2 = eat, 3 = sleep, 4 = dead
void print_status_change(t_philo *philo, char *status)
{
	long	current_time;

	pthread_mutex_lock(&philo->dt->typing);
	current_time = ft_get_current_time();
	
	if (!philo->dt->died)
	{
		printf("%lli ms %i %s", current_time - philo->dt->time_start, philo->id, status);
	}
	pthread_mutex_unlock(&philo->dt->typing);
	return;
}
