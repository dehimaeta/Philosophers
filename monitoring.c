/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 07:00:08 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/08 07:48:38 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_dinner(void *data)
{
	int	i;
	t_table	*table;

	table = (t_table *)data;
	while (!all_threades_running(&table->mutex, &table->running_nbr,
				table->philo_nbr))
		;
	while (!simulation_finished(table))
	{
		i = -1;
		while (++i < table->philo_nbr)
		{
			if (philo_died(table->philo_nbr + i))
			{
				set_bool(&table->mutex, &table->end_stimulations, true);
				write_status(DIED, table->philos + i, DEBUG_MODE);
				
			}
			
		}
		
		
	}

	return (NULL);
}