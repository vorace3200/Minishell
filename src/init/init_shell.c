/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:35:18 by vorace32          #+#    #+#             */
/*   Updated: 2024/10/30 00:35:37 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell_exec.h"

void	init_shell(t_shell *shell, char **env)
{
	shell->env = env;
	shell->input = NULL;
	shell->cmd_list = NULL;
	shell->exit_status = 0;
	shell->is_running = 1;
}
