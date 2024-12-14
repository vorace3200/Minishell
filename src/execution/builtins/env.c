/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 23:31:46 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:22:04 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env && shell->env[i])
	{
		ft_putstr_fd(shell->env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	shell->exit_status = 0;
}
