/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:29:21 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/12 23:29:40 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell_exec.h"

void	builtin_unset(t_shell *shell, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		unset_env_value(shell, args[i]);
		i++;
	}
	shell->exit_status = 0;
}
