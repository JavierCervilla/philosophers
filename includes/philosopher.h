/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 23:53:58 by jcervill          #+#    #+#             */
/*   Updated: 2022/02/28 13:51:03 by jcervill         ###   ########.fr       */
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

# define NUM_PHILOS 0
# define TIME_TO_DIE 1
# define TIME_TO_EAT 2
# define TIME_TO_SLEEP 3
# define NUM_TIMES_EAT 4
# define NUM_ARGS 5

# define TAKING_FORK "has taken a fork"
# define EATING "is eating"
# define DYING "died"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"

# define ERR_BAD_ARGS "\
Usage: ./philosopher <number of philosophers> \
<time to die> <time to eat> <time to sleep> \
<number of time each philosopher will eat>"
# define ERR_INIT "Error: Init"

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

typedef struct s_mutex
{
	pthread_mutex_t mutex;
} t_mutex;

typedef struct s_philo
{
	int id;
	t_status status;
	t_boolean has_left_fork;
	t_boolean has_right_fork;
	int l_fork;
	int r_fork;
	long last_eat;
	int times_eat;
	void	*data;
} t_philo;


typedef struct s_data
{
	long time_start;
	int params[NUM_ARGS];
	t_boolean pause;
	t_philo **philos;
	pthread_mutex_t start;
	pthread_mutex_t *forks;
} t_data;

// UTILS
void		ft_bzero(void *str, size_t n);
int			ft_atoi(char *str);
long		ft_get_miliseconds(struct timeval time_Stamp);
long		ft_get_current_time();
t_boolean	ft_isdigit(int c);
// ERROR
t_boolean	throw_in_error(t_boolean error, char *msg);
// PARSE
int			ft_check_arguments(int argc, char **argv);
int			ft_parse_arguments(t_data *data, int argc, char **argv);
//PHILOSOPHER
t_data		*ft_init_data(t_data *data);
int			ft_init_philosophers(t_data *data);
void		ft_clean(t_data *data);
void		*ft_main_loop (void *args);
//MAIN
t_boolean	ft_check_right_fork (int philo_id, t_data *data);
t_boolean	ft_check_left_fork (int philo_id, t_data *data);
void		take_right_fork(t_philo *philo);
void		take_left_fork(t_philo *philo);
t_boolean	ft_eat(int philo_id, t_data *data);
void		ft_drop_forks(int philo_id, t_data *data, t_forks fork);
void		ft_sleep(int philo_id, t_data *data);
void		ft_think(int philo_id, t_data *data);
//CHECK
int			check_philo_dead(t_data *data);
//PRINT
void		print_status_change(t_philo *philo, t_data data);
#endif