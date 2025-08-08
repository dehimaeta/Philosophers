/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 01:46:29 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/08 18:00:57 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettime(t_time_code timecode)
{
	struct timeval tv;
	
	if (gettimeofday(&tv, NULL))
		error_exit("Zzvcrir eli");
	if (timecode == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (timecode == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));	
	else if (timecode == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Ara es inches tvel es voch varkyana voch mili varkyan vochel micro varkyan");
	return (1337);
}
void	usleep_precise(long usec, t_table *table)
{
	long	start;
	long	elapsed;
	long	rem;
	
	start = gettime(MICROSECOND);
	while (gettime(MICROSECOND) - start < usec)
	{
		if (simulation_finished(table))
			break;
		elapsed = gettime(MICROSECOND) - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (gettime(MICROSECOND) - start < usec)
				;
			
		}
	}
}

void	clean(t_table *table)
{
	t_philo	*philos;
	int		i;
	
	i = -1;
	while (++i < table->philo_nbr)
	{
		philos = table->philos + i;
		safe_mutex(&philos->philo_mutex, DESTROY);
	}
	safe_mutex(&table->write_mutex, DESTROY);
	safe_mutex(&table->mutex, DESTROY);
	free(table->forks);
	free(table->philos);
}

void	error_exit(const char *error)
{
	printf("%s\n", error);
	exit(EXIT_FAILURE);
}