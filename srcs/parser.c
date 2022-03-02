/* ************************************************************************** */
/*	                                                                        */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 01:00:07 by jcervill          #+#    #+#             */
/*   Updated: 2022/02/28 10:30:37 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int ft_check_arguments(int argc, char **argv)
{
	int bad_args;
	int i;
	int j;

	i = 0;
	bad_args = FALSE;
	if (argc > 6 || argc < 5)
		bad_args = TRUE;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				bad_args = TRUE;
		}
	}
	return (bad_args);
}

int ft_parse_arguments(t_data *data, int argc, char **argv)
{
	int i;
	int bad_args;

	bad_args = FALSE;
	i = 0;
	while (i < argc && i < NUM_ARGS)
	{
		data->params[i] = ft_atoi(argv[i + 1]);
		printf("PARAM: %d\n", data->params[i]);
		if (data->params[i] < 1)
			bad_args = TRUE;
		i++;
	}
	return (bad_args);
}