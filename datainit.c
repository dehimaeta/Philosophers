/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   datainit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 03:03:40 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/08 07:36:01 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assing_forks(t_philo *philo, t_fork *forks, int pos)
{
	 int	philo_nbr;

	philo_nbr = philo->table->philo_nbr;

	philo->left_fork = &forks[(pos + 1) % philo_nbr];
	philo->right_fork = &forks[pos];
	if (philo->id % 2 == 0)
	{
		philo->left_fork = &forks[pos];
		philo->right_fork = &forks[(pos + 1) % philo_nbr];
	}
	
}

void philo_init(t_table *table)
{
	int	 i;
	t_philo	*philo;
	
	i = -1;
	while (i++ < table->philo_nbr)
	{
		philo = table->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_counter = 0;
		safe_mutex(&philo->philo_mutex, INIT);

		assing_forks(philo, table->forks, i);
	}
	
}

void	data_init(t_table *table)
{
	int	i;
	
	i = -1;
	table->end_stimulations = false;
	table->all_threads_ready = false;
	table->running_nbr = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	safe_mutex(&table->mutex, INIT);
	safe_mutex(&table->write_mutex, INIT);
	while (++i < table->philo_nbr)
	{
		safe_mutex(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i;
	}
	philo_init(table);
	
}