/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assignment.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:16:52 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/30 00:50:21 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	variable_assignment(t_main_struct *main_struct, char **av)
{
	main_struct->number_of_philo = ft_atoi(av[1]);
	main_struct->time_to_die = ft_atoi(av[2]);
	main_struct->time_to_eat = ft_atoi(av[3]);
	main_struct->time_to_sleep = ft_atoi(av[4]);
	if (!av[5])
		main_struct->eat_number = -1;
	else
		main_struct->eat_number = ft_atoi(av[5]);
	main_struct->all_philos = malloc(sizeof(t_philo)
			* main_struct->number_of_philo);
	if (!main_struct->all_philos)
		return (-1);
	main_struct->forks_mutex = malloc(sizeof(pthread_mutex_t)
			* main_struct->number_of_philo);
	if (!main_struct->forks_mutex)
		return (-1);
	return (0);
}

void	assign_start_time(t_main_struct *main_struct)
{
	int	i;

	i = 0;
	main_struct->start_time = get_current_millis();
	while (i < main_struct->number_of_philo)
	{
		pthread_mutex_lock(&main_struct->meal_mutex);
		main_struct->all_philos[i].last_meal_time = main_struct->start_time;
		pthread_mutex_unlock(&main_struct->meal_mutex);
		i++;
	}
}
