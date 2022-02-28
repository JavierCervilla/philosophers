/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcervill <jcervill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 11:37:25 by jcervill          #+#    #+#             */
/*   Updated: 2022/02/28 13:25:56 by jcervill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_boolean	throw_in_error(t_boolean error, char *msg)
{
	if (error == TRUE)
	{
		perror(msg);
		// TODO: REDIR TO EXIT OR EXIT HERE
	}
	return (error);

}