/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synchro.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 02:59:26 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/08 07:42:27 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_threads(t_table *table)
{
	//spinlock
	while(!get_bool(&table->mutex, &table->all_threads_ready))
		;	
}
bool	all_threades_running(t_fork *mutex, long *threads,
		long philo_nbr)
{
	bool	res;
	
	res = false;
	safe_mutex(mutex, LOCK);
	if (*threads == philo_nbr)
		res = true;
	safe_mutex(mutex, UNLOCK);
	return(res);
}

void	increase_long(t_mutex *mutex, long *value)
{
	safe_mutex(mutex, LOCK);
	(*value)++;
	safe_mutex(mutex, UNLOCK);
}
