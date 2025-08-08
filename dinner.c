/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:55:19 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/08 07:42:54 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	write(THINKING, philo, DEBUG_MODE);
	
}

void	eat(t_philo *philo)
{
	safe_mutex(&philo->left_fork->fork, LOCK);
	write_status(TAKE_LEFT_FORK, philo, DEBUG_MODE);
	safe_mutex(&philo->right_fork->fork, LOCK);
	write_status(TAKE_RIGHT_FORK, philo, DEBUG_MODE);
	
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo, DEBUG_MODE);
	usleep_precise(philo->table->time_to_eat, philo->table);
	if (philo->table->limit_meals > 0
		&& philo->meals_counter == philo->table->limit_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	
	safe_mutex(&philo->right_fork->fork, UNLOCK);
	safe_mutex(&philo->left_fork->fork, UNLOCK);
}

void 	*simulation(void *data)
{
	t_philo	*philo;
	
	philo = (t_philo *)data;
	
	wait_threads(philo->table);
	
	increase_long(&philo->table->mutex,
		&philo->table->running_nbr);
	
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);

		write_status(SLEEPING, philo, DEBUG_MODE);
		usleep_precise(philo->table->time_to_sleep, philo->table);
		
		thinking(philo);
	}
	
	return (NULL);
}

void	dinner_start(t_table *table)
{
	int	i;

	i = -1;
	
	if (table->limit_meals == 0)
		return ;
	else if(table->philo_nbr == 1)
		; // TODO
	else
	{
		while (++i < table->philo_nbr)
			safe_thread(&table->philos[i].thread_id, simulation,
				&table->philos[i], CREATE);
	}
	safe_thread(&table->monitor, monitor_dinner, table, CREATE);
	
	table->start_simulations = gettime(MILLISECOND);
	
	set_bool(&table->mutex, &table->all_threads_ready, true);
	
	i = -1;
	while (++i < table->philo_nbr)
		safe_thread(&table->philos[i].thread_id, NULL, NULL, JOIN);
	
}