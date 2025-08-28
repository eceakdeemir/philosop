/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:51:08 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/28 17:53:03 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct s_main_struct t_main_struct;

typedef struct s_philo
{
	int flag;
	int philo_id;
	int total_meal_number;
	long last_meal_time;
	pthread_t filo_thread;
	t_main_struct *main_ref;
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
} t_philo;

typedef struct s_main_struct
{
	int time_to_eat;
	int time_to_sleep;
	int number_of_philo;
    int time_to_die;
    int stop_control;
    short died_id;
	int number_of_times_to_eat;
	t_philo *all_philos;
	pthread_t the_angel_of_death;
	pthread_mutex_t stop_mutex;
	pthread_mutex_t *forks_mutex;
	pthread_mutex_t message_mutex;
	long start_time;
} t_main_struct;


// ----arg_error_check------
int	ft_is_all_digit(char *arg_str);
int	ft_atoi(const char *str);
int arg_parse(char *arg_str);
int arg_number(int ac, char **av);
int arg_check_error(int ac, char **av);

//-----assignment-------
int variable_assignment(t_main_struct *main_struct, char **av);

//------init_destroy_mutex------
void destroy_mutex(t_main_struct *main_struct, int init_number);
int init_mutex(t_main_struct *main_struct);


#endif