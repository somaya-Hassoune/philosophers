/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shassoun <shassoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 22:27:23 by shassoun          #+#    #+#             */
/*   Updated: 2024/10/10 00:12:13 by shassoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	ft_atoi(char *str)
{
	int		i;
	long	res;
	int		flag;

	i = 0;
	res = 0;
	flag = 0;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		flag = 1;
		res = res * 10 + (str[i] - 48);
		if (res > INT_MAX)
			return (-1);
		i++;
	}
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] != '\0' || flag != 1)
		return (printf("Error \n"), -1);
	return (res);
}
