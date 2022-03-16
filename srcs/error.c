/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 11:37:25 by jcervill          #+#    #+#             */
/*   Updated: 2022/03/16 13:50:42 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_boolean	throw_in_error(t_boolean error, char *msg)
{
	if (error == TRUE)
		perror(msg);
	return (error);
}
