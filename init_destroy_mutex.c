/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy_mutex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 17:46:28 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/29 22:56:21 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_main_struct *main_struct, int init_number)
{
	int	i;

	i = 0;
	if (init_number == 0)
	{
		while (i < main_struct->number_of_philo)
		{
			pthread_mutex_destroy(&(main_struct->forks_mutex[i]));
			i++;
		}
	}
	else
	{
		while (i < init_number)
		{
			pthread_mutex_destroy(&(main_struct->forks_mutex[i]));
			i++;
		}
	}
}

int	init_mutex(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	while (i < main_struct->number_of_philo)
	{
		if (pthread_mutex_init(&(main_struct->forks_mutex[i]), NULL) != 0)
		{
			destroy_mutex(main_struct, i);
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_init(&(main_struct->message_mutex), NULL) != 0)
	{
		destroy_mutex(main_struct, 0);
		return (-1);
	}
	if (pthread_mutex_init(&(main_struct->stop_mutex), NULL) != 0)
	{
		destroy_mutex(main_struct, 0);
		pthread_mutex_destroy(&(main_struct->message_mutex));
		return (-1);
	}
	return (0);
}
