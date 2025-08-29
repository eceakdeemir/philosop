/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:08:42 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/29 23:01:58 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all(t_main_struct *main_struct)
{
	destroy_mutex(main_struct, 0);
	pthread_mutex_destroy(&main_struct->message_mutex);
	pthread_mutex_destroy(&main_struct->stop_mutex);
	free(main_struct->all_philos);
	free(main_struct->forks_mutex);
	free(main_struct);
}

int	assign_and_init(t_main_struct *main_struct, char **av)
{
	if (variable_assignment(main_struct, av) == -1)
	{
		free(main_struct);
		return (1);
	}
	if (init_mutex(main_struct) == -1)
	{
		free(main_struct);
		return (1);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_main_struct	*main_struct;
	int				i;

	i = 0;
	if (arg_check_error(ac, av) == -1)
		return (1);
	main_struct = malloc(sizeof(t_main_struct));
	if (!main_struct)
		return (0);
	main_struct->died_id = -1;
	if (assign_and_init(main_struct, av))
		return (1);
	create_philo_array(main_struct);
	assign_start_time(main_struct);
	create_philo_thread(main_struct);
	pthread_create(&main_struct->the_angel_of_death, NULL,
		monitor_thread_dead_control, main_struct);
	while (i < main_struct->number_of_philo)
	{
		pthread_join(main_struct->all_philos[i].filo_thread, NULL);
		i++;
	}
	pthread_join(main_struct->the_angel_of_death, NULL);
	destroy_all(main_struct);
}
