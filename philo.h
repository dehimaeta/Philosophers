/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 01:13:15 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/07 01:13:15 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>
#include <string.h>
#include <errno.h>

#	define DEBUG_MODE 0

typedef	enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_LEFT_FORK,
	TAKE_RIGHT_FORK,
	DIED,
}			t_philo_status;

typedef	enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}			t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}			t_time_code;

typedef	pthread_mutex_t t_mutex;
typedef struct s_table t_table;

typedef struct s_fork
{
	t_mutex	fork;
	int		fork_id;
}				t_fork;


typedef struct s_philo
{
	int				id;
	int				meals_counter;
	bool			full;
	long			last_meal_time;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread_id;
	t_mutex			philo_mutex;
	t_table			*table;
}					t_philo;

struct s_table
{
	long	philo_nbr;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	limit_meals;
	long	start_simulations;
	bool	end_stimulations;
	bool	all_threads_ready;
	long	running_nbr;
	pthread_t	monitor;
	t_mutex	mutex;
	t_mutex	write_mutex;
	t_fork	*forks;
	t_philo	*philos;
};


void	error_exit(const char *error);
void	parse_input(t_table *table, char **argv);
void	data_init(t_table *table);
void	*safe_malloc(size_t bytes);
void	safe_mutex(t_mutex *mutex, t_opcode opcode);
void	safe_thread(pthread_t *thread, void *(*f)(void *), void *data, t_opcode opcode);
void	set_bool(t_mutex *mutex, bool *dest, bool value);
bool	get_bool(t_mutex *mutex, bool *value);
long	get_long(t_mutex *mutex, long *value);
void	set_long(t_mutex *mutex, long *dest, long value);
bool	simulation_finished(t_table *table);
void	wait_threads(t_table *table);
long	gettime(t_time_code timecode);
void	usleep_precise(long usec, t_table *table);
void	write_status(t_philo_status status, t_philo *philo, bool debug);
void	dinner_start(t_table *table);
void	clean(t_table *table);

#endif