/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 19:08:42 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/28 22:36:48 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_main_struct *main_struct;
	
	if (arg_check_error(ac, av) == -1)	
		return (1);
	main_struct = malloc(sizeof(t_main_struct));
	if (!main_struct)
		return (0);
	main_struct->died_id = -1;
	if (variable_assignment(main_struct, av) == -1)
		return (1);
	if(init_mutex(main_struct) == -1)
		return (1);
	create_philo_array(main_struct);
	assign_start_time(main_struct);
	
}
