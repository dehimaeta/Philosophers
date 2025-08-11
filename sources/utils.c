/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 01:46:29 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/11 21:02:36 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	gettime(t_time_code timecode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("Zzvcrir eli");
	if (timecode == SECOND)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (timecode == MILLISECOND)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	else if (timecode == MICROSECOND)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("Eeee de normal time tur");
	return (1337);
}

void	usleep_precise(long milliseconds)
{
	long	start;

	start = gettime(MILLISECOND);
	while ((gettime(MILLISECOND) - start) < milliseconds)
		usleep(500);
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
