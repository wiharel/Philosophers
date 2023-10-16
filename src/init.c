/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiharel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:51:41 by wiharel           #+#    #+#             */
/*   Updated: 2022/08/23 14:51:42 by wiharel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_mutex(t_data *data)
{
	int		i;

	if (pthread_mutex_init(&data->m_life, NULL))
		return (1);
	i = -1;
	while (++i < data->nb_philos)
	{
		if (pthread_mutex_init(&data->m_forks[i], NULL))
			return (1);
	}
	return (M_SUCCESS);
}

static int	init_threads(t_data *data, t_time *time)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->nb_philos)
	{
		philo = &data->philos[i];
		philo->num = i + 1;
		philo->eat_count = 0;
		philo->ms_to_die = time->ms_to_die;
		philo->time = time;
		philo->data = data;
		philo->i_fork1 = i;
		philo->i_fork2 = (i + 1) % data->nb_philos;
		if (pthread_create(&philo->thread, NULL,
				(void *)&routine, (void *) philo) != M_SUCCESS)
			return (1);
		++i;
	}
	return (M_SUCCESS);
}

int	init(t_data *data, t_time *time)
{
	time->ms_start = get_time();
	data->philos = malloc(sizeof(t_philo) * data->nb_philos);
	data->m_forks = malloc(sizeof(pthread_mutex_t) * data->nb_philos);
	if (data->philos == NULL || data->m_forks == NULL)
		return (print_error_i("malloc error"));
	memset(data->philos, 0, sizeof(t_philo) * data->nb_philos);
	if (init_mutex(data) != M_SUCCESS)
		return (print_error_i("mutex init"));
	if (init_threads(data, time) != M_SUCCESS)
		return (print_error_i("thread create/join"));
	return (M_SUCCESS);
}
