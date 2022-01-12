/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:45:02 by jcervill          #+#    #+#             */
/*   Updated: 2022/01/12 14:09:25 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int ft_main_loop (t_data *data)
{
    int i;

    i = -1;
    while(!data->pause){
        // iteramos en los philos
        // - check for right fork:
        //      - si:
        //          - has left fork?
        //              - si:
        //                  eat()
        //                  soltar_forks()
        //                  sleep()
        //                  next()    
        //              - no:
        //                  previous has right fork?
        //                      - si:
        //                          soltar_forks()
        //                          next()
        //                      - no:
        //                          take_left_fork()
        //                          eat()
        //                          soltar_forks()
        //                          sleep()
        //                          next()
        //      - no:
        //          - nextone has right fork?
        //              - si: 
        //                  next()
        //              - no: 
        //                  take_right_fork     
        while(++i < data->nb_philo)
        {
            //1. PHILO HAS RIGHT FORK?
            if (ft_check_right_fork(i, data))
            {
                //YES
                //1.2. PHILO HAS LEFT FORK?
                if (ft_check_left_fork(i, data))
                {
                    // YES
                    // EAT
                    // DROP FORKS
                    // SLEEP
                    // NEXT
                }
                // NO
                else
                {
                    //1.3. PREVIOUS HAS RIGHT?
                    if (ft_check_right_fork(i - 1 % data->nb_philo, data))
                    {
                        // YES
                        // DROP FORKS
                        // NEXT
                    }
                    else
                    {
                        // NO
                        take_left_fork(data->philos[i]);
                        // EAT
                        // DROP FORKS
                        // NEXT
                    }
                }
            }
            else
            {
                // NO
                // NEXT HAS RIGHT?
                if (ft_check_right_fork(i + 1 % data->nb_philo, data))
                {
                    // NEXT
                }
                else
                {
                    take_right_fork(data->philos[i]);
                    //NEXT or START again
                }
            }
        }
        i = -1;
    }
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

int take_right_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->right_fork);
    philo->has_right_fork = TRUE;
    printf("Philo Nº%d takes right fork");
    return 1;
}

int take_left_fork(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    philo->has_left_fork = TRUE;
    printf("Philo Nº%d takes left fork");
    return 1;
}