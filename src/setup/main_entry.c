/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:53:50 by vorace32          #+#    #+#             */
/*   Updated: 2024/11/04 15:17:35 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell_exec.h"

void	main_entry(t_shell *shell)
{
	main_parsing(shell);
	execute_commands(shell);
	free_commands(shell->cmd_list);
	shell->cmd_list = NULL;
}
