/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 01:55:19 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/08 19:50:35 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, bool simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!simulation)
		write(THINKING, philo, DEBUG_MODE);

	if (philo->table->philo_nbr % 2 == 0)
		return ;
	t_eat = philo->table->time_to_eat;
	t_sleep = philo->table->time_to_sleep;
	t_think = t_eat  * 2 - t_sleep;
	if (t_think < 0)
		t_think = 0;
	usleep_precise(t_think * 0.42, philo->table);
}

void	*one_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	
	wait_threads(philo->table);
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	write_status(TAKE_LEFT_FORK, philo);
	
	while (!simulation_finished(philo->table))
		usleep(200);
	return (NULL);
}

void	eat(t_philo *philo)
{
	safe_mutex(&philo->left_fork->fork, LOCK);
	write_status(TAKE_LEFT_FORK, philo);
	safe_mutex(&philo->right_fork->fork, LOCK);
	write_status(TAKE_RIGHT_FORK, philo);
	
	set_long(&philo->philo_mutex, &philo->last_meal_time, gettime(MILLISECOND));
	philo->meals_counter++;
	write_status(EATING, philo);
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

	set_long(&philo->philo_mutex, &philo->last_meal_time,
			gettime(MILLISECOND));
	synchronize_philos(philo);
	increase_long(&philo->table->mutex,
		&philo->table->running_nbr);
	
	while (!simulation_finished(philo->table))
	{
		if (philo->full)
			break ;
		eat(philo);

		write_status(SLEEPING, philo);
		usleep_precise(philo->table->time_to_sleep, philo->table);
		
		thinking(philo, false);
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
		safe_thread(&table->philos[0].thread_id, one_philo,
				&table->philos[0], CREATE);
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
		
	set_bool(&table->mutex, &table->end_stimulations, true);
	
	safe_thread(&table->monitor, NULL, NULL, JOIN);
}