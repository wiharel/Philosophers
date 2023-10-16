/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiharel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:51:58 by wiharel           #+#    #+#             */
/*   Updated: 2022/08/23 14:51:59 by wiharel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *param)
{
	t_philo	*philo;

	philo = param;
	if (philo->num % 2 == 0)
		sleep_ajusted(philo->time->ms_to_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->data->m_life);
		if (philo->data->first_dead)
		{
			pthread_mutex_unlock(&philo->data->m_life);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->m_life);
		if (philo->time->count_to_eat
			&& philo->time->count_to_eat == philo->eat_count)
			return (NULL);
		r_take_fork(philo);
		r_eat(philo);
		r_sleep(philo);
		r_think(philo);
	}
	return (NULL);
}
