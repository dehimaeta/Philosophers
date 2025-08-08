/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/08 05:32:56 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/08 19:51:00 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	int elapsed;

	elapsed = gettime(MILLISECOND);
	if (philo->full)
		return ;
	safe_mutex(&philo->table->write_mutex, LOCK);
	if ((status == TAKE_LEFT_FORK || status == TAKE_RIGHT_FORK)
		&& !simulation_finished(philo->table))
		printf("%d %d has taken a fork\n",elapsed, philo->id);
	else if (status == EATING && !simulation_finished(philo->table))
		printf("%d %d is eating\n",elapsed, philo->id);
	else if (status == SLEEPING && !simulation_finished(philo->table))
		printf("%d %d is sleeping\n",elapsed, philo->id);
	else if (status == THINKING && !simulation_finished(philo->table))
		printf("%d %d is thinking\n",elapsed, philo->id);
	else if (status == DIED)
		printf("%d %d died\n",elapsed, philo->id);

	safe_mutex(&philo->table->write_mutex, UNLOCK);
}
