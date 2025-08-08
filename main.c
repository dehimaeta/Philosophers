/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalkhas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 01:40:45 by rmalkhas          #+#    #+#             */
/*   Updated: 2025/08/08 19:53:23 by rmalkhas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_table table;
	
	if (argc == 5 || argc == 6)
	{
		parse_input(&table, argv);
		
		data_init(&table);
		
		dinner_start(&table);

		clean(&table);
	}
	else
	{
		error_exit("Wrong input:\n");
	}
	return 0;
}
