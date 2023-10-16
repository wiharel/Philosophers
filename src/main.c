/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wiharel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 14:51:52 by wiharel           #+#    #+#             */
/*   Updated: 2022/08/23 14:51:54 by wiharel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_philo(int ms_to_die)
{
	printf("0	1	has taken a fork\n");
	sleep_ajusted(ms_to_die);
	return (printf("%d	1	died\n", ms_to_die));
}

static int	parse(t_data *data, t_time *time, char **av)
{
	int	i;

	i = 0;
	while (av[++i])
	{
		if (ft_atoi(av[i]) > 0)
		{
			if (i == 2)
				time->ms_to_die = ft_atoi(av[2]);
			else if (i == 3)
				time->ms_to_eat = ft_atoi(av[3]);
			else if (i == 4)
				time->ms_to_sleep = ft_atoi(av[4]);
			else if (i == 5)
				time->count_to_eat = ft_atoi(av[5]);
		}
		else
			return (print_error_u("each args must be numeric"));
	}
	if (ft_atoi(av[1]) > 200)
		return (print_error_u("You can't do >200"));
	if (ft_atoi(av[1]) == 1)
		return (one_philo(time->ms_to_die));
	data->nb_philos = ft_atoi(av[1]);
	return (0);
}

static int	all_ate(t_data *data, t_time *time)
{
	int	i;

	i = 0;
	if (time->count_to_eat == 0)
		return (0);
	while (i < data->nb_philos)
	{
		if (data->philos[i].eat_count != time->count_to_eat)
			return (0);
		++i;
	}
	return (1);
}

static void	watch(t_data *data, t_time *time)
{
	int		i;

	i = 0;
	while (data->all_ate == 0)
	{
		pthread_mutex_lock(&data->m_life);
		data->ms_current = get_time() - time->ms_start;
		if (data->ms_current >= data->philos[i].ms_to_die)
		{
			data->first_dead = i + 1;
			printf("%lld	%d	is dead\n",
				data->ms_current, data->first_dead);
			pthread_mutex_unlock(&data->m_life);
			break ;
		}
		data->all_ate = all_ate(data, time);
		i = (i + 1) % data->nb_philos;
		pthread_mutex_unlock(&data->m_life);
		usleep(2500);
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	t_time	time;

	if (ac < 5 || ac > 6)
		return (print_error_u("arguments not valid 5 or 6\n"));
	memset(&data, 0, sizeof(t_data));
	memset(&time, 0, sizeof(t_time));
	if (parse(&data, &time, av) == M_SUCCESS && init(&data, &time) == M_SUCCESS)
	{
		watch(&data, &time);
		if (all_ate(&data, &time))
			printf("All philosophers have eaten! MIAM\n");
	}
	destroy_all(&data);
	free_all(&data);
	return (M_SUCCESS);
}
