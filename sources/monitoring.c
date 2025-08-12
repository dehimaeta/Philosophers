/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 07:00:08 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/12 18:42:54 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	lock_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->left_fork->fork_id < philo->right_fork->fork_id)
	{
		first_fork = &philo->left_fork->fork;
		second_fork = &philo->right_fork->fork;
	}
	else
	{
		first_fork = &philo->right_fork->fork;
		second_fork = &philo->left_fork->fork;
	}
	safe_mutex(first_fork, LOCK);
	write_status(TAKE_FORK, philo);
	safe_mutex(second_fork, LOCK);
	write_status(TAKE_FORK, philo);
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->left_fork->fork_id < philo->right_fork->fork_id)
	{
		first_fork = &philo->left_fork->fork;
		second_fork = &philo->right_fork->fork;
	}
	else
	{
		first_fork = &philo->right_fork->fork;
		second_fork = &philo->left_fork->fork;
	}
	safe_mutex(second_fork, UNLOCK);
	safe_mutex(first_fork, UNLOCK);
}

bool	philo_died(t_philo *philo)
{
	long	elapsed;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	if (elapsed > philo->table->time_to_die)
		return (true);
	return (false);
}

void	*monitor_dinner(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threades_running(&table->mutex, &table->running_nbr,
			table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr && !simulation_finished(table))
		{
			if (philo_died(table->philos + i) && table->philo_nbr != 1)
			{
				set_bool(&table->mutex, &table->end_stimulations, true);
				write_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}
