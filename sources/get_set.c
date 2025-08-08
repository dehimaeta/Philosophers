/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 06:21:49 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/09 03:25:33 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	set_bool(t_mutex *mutex, bool *dest, bool value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

bool	get_bool(t_mutex *mutex, bool *value)
{
	bool	res;

	safe_mutex(mutex, LOCK);
	res = *value;
	safe_mutex(mutex, UNLOCK);
	return (res);
}

long	get_long(t_mutex *mutex, long *value)
{
	long	res;

	safe_mutex(mutex, LOCK);
	res = *value;
	safe_mutex(mutex, UNLOCK);
	return (res);
}

void	set_long(t_mutex *mutex, long *dest, long value)
{
	safe_mutex(mutex, LOCK);
	*dest = value;
	safe_mutex(mutex, UNLOCK);
}

bool	simulation_finished(t_table *table)
{
	return (get_bool(&table->mutex, &table->end_stimulations));
}
