/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecakdemi <ecakdemi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 16:51:08 by ecakdemi          #+#    #+#             */
/*   Updated: 2025/08/29 23:16:34 by ecakdemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_main_struct	t_main_struct;

typedef struct s_philo
{
	int							flag;
	int							philo_id;
	int							total_meal_number;
	long						last_meal_time;
	pthread_t					filo_thread;
	t_main_struct				*main_ref;
	pthread_mutex_t				*left_fork;
	pthread_mutex_t				*right_fork;
}								t_philo;

typedef struct s_main_struct
{
	int							time_to_eat;
	int							time_to_sleep;
	int							number_of_philo;
	int							time_to_die;
	int							stop_control;
	short						died_id;
	int							eat_number;
	long						start_time;
	t_philo						*all_philos;
	pthread_t					the_angel_of_death;
	pthread_mutex_t				stop_mutex;
	pthread_mutex_t				*forks_mutex;
	pthread_mutex_t				message_mutex;
}								t_main_struct;

int								ft_is_all_digit(char *arg_str);
int								ft_atoi(const char *str);
int								arg_parse(char *arg_str);
int								arg_number(int ac, char **av);
int								arg_check_error(int ac, char **av);
int								variable_assignment(t_main_struct *main_struct,
									char **av);
void							assign_start_time(t_main_struct *main_struct);
void							destroy_mutex(t_main_struct *main_struct,
									int init_number);
int								init_mutex(t_main_struct *main_struct);
void							create_philo_array(t_main_struct *main_struct);
void							create_philo_thread(t_main_struct *main_struct);
unsigned long					get_current_millis(void);
void							ft_msleep(unsigned long mls);
void							take_forks(t_philo *philo);
void							*routine(void *philosophers);
void							saying_act(t_philo *philo, char *message,
									int flag);
int								one_philo_dead_control_for_monitor(
									t_philo *philo);
void							*monitor_thread_dead_control(void *main_struct);

#endif