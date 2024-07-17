/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:05:05 by quanguye          #+#    #+#             */
/*   Updated: 2024/07/17 16:05:11 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*update_remainder(char *remainder, char *new_line_position)
{
	char	*temp;

	temp = ft_strdup(new_line_position + 1);
	free(remainder);
	return (temp);
}

char	*free_remainder(char **remainder)
{
	free(*remainder);
	*remainder = NULL;
	return (NULL);
}
