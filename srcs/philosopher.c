/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:45:02 by jcervill          #+#    #+#             */
/*   Updated: 2022/01/17 13:49:04 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void *ft_main_loop (void *args)
{
    t_data *data;
    int i;

    i = -1;
    data = (t_data *)args;
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
            printf("LLEGO");
            //1. PHILO HAS RIGHT FORK?
            if (ft_check_right_fork(i, data))
            {
                //YES
                //1.2. PHILO HAS LEFT FORK?
                if (ft_check_left_fork(i, data))
                {
                    printf("philo N-%d has both forks and will start eating\n", i);
                    // YES
                    // EAT
                    ft_eat(i, data);
                    // DROP FORKS
                    ft_drop_forks(i, data, BOTH);
                    // SLEEP
                    ft_sleep(i, data);
                    // NEXT
                    continue;
                }
                // NO
                else
                {
                    //1.3. PREVIOUS HAS RIGHT?
                    if (ft_check_right_fork(i - 1 % data->nb_philo, data))
                    {
                        // YES
                        // DROP FORKS
                        ft_drop_forks(i, data, RIGHT);
                        // NEXT
                        continue;
                    }
                    else
                    {
                        // NO
                        take_left_fork(data->philos[i]);
                        // EAT
                        ft_eat(i, data);
                        // DROP FORKS
                        ft_drop_forks(i, data, BOTH);
                        // NEXT
                        continue;
                    }
                }
            }
            else
            {
                // NO
                // NEXT HAS RIGHT?
                if (ft_check_right_fork(i + 1 % data->nb_philo, data))
                {
                    continue;
                    // NEXT
                }
                else
                {
                    take_right_fork(data->philos[i]);
                    //NEXT or START again
                    continue;
                }
            }
            print_status_change(data->philos[i], *data);

        }
        i = -1;
    }
    
    return((void *)data);
}


t_boolean ft_eat(int philo_id, t_data *data)
{
    t_philo *philo;
    
    philo = data->philos[philo_id];
    philo->last_eat = ft_get_current_time();
    philo->times_eat++;
    philo->status = EAT;
    sleep((unsigned int)data->time_to_eat);
    if (philo->times_eat == data->nb_times_must_eat)
        return TRUE;
    print_status_change(data->philos[philo_id], *data);
    return FALSE;
}

void ft_think(int philo_id, t_data *data)
{
    t_philo *philo;

    philo = data->philos[philo_id];
    philo->status = THINK;
    print_status_change(data->philos[philo_id], *data);
}

void ft_sleep(int philo_id, t_data *data)
{
    t_philo *philo;

    philo = data->philos[philo_id];
    philo->status = SLEEP;
    print_status_change(philo, *data);
    sleep(data->time_to_sleep);
    print_status_change(data->philos[philo_id], *data);
}

void ft_drop_forks(int philo_id, t_data *data, t_forks fork)
{
    t_philo *philo;

    philo = data->philos[philo_id];
    if (fork == LEFT || fork == BOTH)
        pthread_mutex_unlock(&philo->left_fork);
    if (fork == RIGHT || fork == BOTH)
        pthread_mutex_unlock(&philo->right_fork);
    print_status_change(data->philos[philo_id], *data);
    
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
    pthread_mutex_lock(&philo->right_fork);
    philo->has_right_fork = TRUE;
    printf("Philo Nº%d takes right fork", philo->id);
    return 1;
}

int take_left_fork(t_philo *philo)
{
    pthread_mutex_lock(&philo->left_fork);
    philo->has_left_fork = TRUE;
    printf("Philo Nº%d takes left fork", philo->id);
    return 1;
}