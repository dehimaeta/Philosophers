/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 07:00:08 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/09 03:31:05 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	philo_died(t_philo *philo)
{
	long	elapsed;
	long	to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	elapsed = gettime(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	to_die = philo->table->time_to_die / 1e3;
	if (elapsed > to_die)
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
			if (philo_died(table->philos + i))
			{
				set_bool(&table->mutex, &table->end_stimulations, true);
				write_status(DIED, table->philos + i);
			}
		}
	}
	return (NULL);
}
