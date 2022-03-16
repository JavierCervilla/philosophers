/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 23:53:58 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/16 13:34:51 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>
# define MAX_INT 2147483647
# define TAKING_FORK "has taken a fork\n"
# define EATING "is eating\n"
# define THINKING "is thinking\n"
# define SLEEPING "is sleeping\n"
# define DROPING_FORK "has dropen a fork\n"
# define DYING "died"
# define ERR_BAD_ARGS "\
Usage: ./philosopher <number of philosophers> \
<time to die> <time to eat> <time to sleep> \
<number of time each philosopher will eat>"
# define ERR_INIT "Error: Initiaizing program."
# define ERR_INIT_PHILO "Error: Initializing Philos."
# define ERR_INIT_TH "Error: Initializing Philo`s threads."
# define STATUS_NO_ERR 0
# define STATUS_ERR 1

typedef enum e_args
{
	NUM_PHILOS,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUM_TIMES_EAT,
	NUM_ARGS
}	t_args;

typedef enum e_boolean
{
	FALSE,
	TRUE
}	t_boolean;

typedef enum e_forks
{
	LEFT,
	RIGHT,
	BOTH
}	t_forks;

typedef enum e_status
{
	THINK,
	EAT,
	SLEEP,
	DEAD
}	t_status;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
}	t_mutex;

typedef struct s_philo
{
	int				id;
	t_status		status;
	pthread_t		th;
	pthread_mutex_t	*has_left_fork;
	pthread_mutex_t	*has_right_fork;
	int				plenty;
	long long		last_eat;
	int				times_eat;
	struct s_data	*dt;
}	t_philo;

typedef struct s_data
{
	long long		time_start;
	int				params[NUM_ARGS];
	int				died;
	int				all_eaten;
	t_philo			*philos;
	pthread_mutex_t	start;
	pthread_mutex_t	typing;
	pthread_mutex_t	*forks;
}	t_data;

// UTILS
void		ft_bzero(void *str, size_t n);
int			ft_atoi(char *str);
long long	ft_get_current_time(void);
long long	diff_time(long long t1, long long t2);
t_boolean	ft_isdigit(int c);
void		smart_sleep(int time);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_putnbr(int nb);
// ERROR
t_boolean	throw_in_error(t_boolean error, char *msg);
// PARSE
int			ft_check_arguments(int argc, char **argv);
int			ft_parse_arguments(t_data *data, int argc, char **argv);
//PHILOSOPHER
t_data		*ft_init_data(t_data *data);
int			ft_lonley_philo(t_data *data);
int			ft_init_philosophers(t_data *data);
int			ft_init_threads(t_data *data);
void		ft_clean(t_data *data);
void		*eat_think_sleep(void *philo_address);
//MAIN
void		eating_routine(t_philo *philo);
t_boolean	ft_check_right_fork(t_philo *philo);
t_boolean	ft_check_left_fork(t_philo *philo);
void		take_right_fork(t_philo *philo);
void		take_left_fork(t_philo *philo);
void		ft_eat(t_philo *philo);
void		ft_drop_forks(t_philo *philo);
void		ft_sleep(t_philo *philo);
void		ft_think(t_philo *philo);
//CHECK
void		ft_control_threads(t_data *data);
//PRINT
void		print_status_change(t_philo *philo, char *status);
#endif