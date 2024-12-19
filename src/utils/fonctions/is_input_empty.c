/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_input_empty.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrunier <tbrunier@student.42perpignan.fr> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 15:27:22 by tbrunier          #+#    #+#             */
/*   Updated: 2024/12/19 15:38:58 by tbrunier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	is_input_empty(char *input)
{
	unsigned int	i;

	i = 0;
	while (input[i])
	{
		if (!(input[i] == '\t'))
			return (0);
		i++;
	}
	return (1);
}
