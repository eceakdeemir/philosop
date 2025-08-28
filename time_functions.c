/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 20:09:07 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/28 20:09:21 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long get_current_millis()
{
    struct timeval time_value;
	gettimeofday(&time_value, NULL);
	return (time_value.tv_sec * 1000 + time_value.tv_usec / 1000);
}