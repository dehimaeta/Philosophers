/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 02:06:24 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/09 03:33:03 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

const	char	*valid_input(const char *str)
{
	int			len;
	int			i;
	const char	*number;

	i = 0;
	len = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		error_exit("asenq minus tiv es tvel inch anem sra het!");
	if (!is_digit(str[i]))
		error_exit("axper dzer es arnum esi tiv chi!!!");
	number = str;
	while ((is_digit(str[i])))
	{
		i++;
		len++;
	}
	if (len > 10)
		error_exit("hamy hanum es INT_MAX ic poqr tiv tur!");
	return (number);
}

long	ft_atol(const char *str)
{
	long	num;
	int		i;

	i = 0;
	num = 0;
	str = valid_input(str);
	while (is_digit(str[i]))
		num = (num * 10) + (str[i++] - '0');
	if (num > INT_MAX)
		error_exit("hamy hanum es INT_MAX ic poqr tiv tur!");
	return (num);
}

void	parse_input(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	table->time_to_die = ft_atol(argv[2]);
	table->time_to_eat = ft_atol(argv[3]);
	table->time_to_sleep = ft_atol(argv[4]);
	if (argv[5] != NULL)
		table->limit_meals = ft_atol(argv[5]);
	else
		table->limit_meals = -1;
}
