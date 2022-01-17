/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 23:53:58 by jcervill          #+#    #+#             */
/*   Updated: 2022/01/17 13:41:00 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSHOPHER_H
#define PHILOSHOPHER_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

typedef enum e_boolean
{
    FALSE,
    TRUE
} t_boolean;

typedef enum e_forks
{
    LEFT,
    RIGHT,
    BOTH
} t_forks;

typedef enum e_status
{
    THINK,
    TAKE_FORK,
    EAT,
    SLEEP,
    DEAD
} t_status;

typedef struct s_philo
{
    int id;
    t_status status;
    t_boolean has_left_fork;
    t_boolean has_right_fork;
    pthread_mutex_t left_fork;
    pthread_mutex_t right_fork;
    pthread_t philo_thread;
    long last_eat;
    int times_eat;
} t_philo;

typedef struct s_data
{
    long time_start;
    int nb_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int nb_times_must_eat;
    t_boolean pause;
    t_philo **philos;
    pthread_mutex_t start;
} t_data;

// UTILS
int ft_atoi(char *str);
long ft_get_miliseconds(struct timeval time_Stamp);
long ft_get_current_time();
t_boolean ft_isdigit(int c);
// PARSE
int ft_check_arguments(int argc, char **argv);
int ft_parse_arguments(t_data *data, int argc, char **argv);
//PHILOSOPHER
int ft_init_data(t_data *data);
int ft_init_philosophers(t_data *data);
void ft_clean(t_data *data);
void *ft_main_loop (void *args);
//MAIN
t_boolean ft_check_right_fork (int philo_id, t_data *data);
t_boolean ft_check_left_fork (int philo_id, t_data *data);
int take_right_fork(t_philo *philo);
int take_left_fork(t_philo *philo);
t_boolean ft_eat(int philo_id, t_data *data);
void ft_drop_forks(int philo_id, t_data *data, t_forks fork);
void ft_sleep(int philo_id, t_data *data);
void ft_think(int philo_id, t_data *data);
//CHECK
int check_philo_dead(t_data *data);
//PRINT
void print_status_change(t_philo *philo, t_data data);
#endif