/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 11:58:47 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/16 12:50:28 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	save_std_fds(int *saved_stdin, int *saved_stdout)
{
	*saved_stdin = dup(STDIN_FILENO);
	*saved_stdout = dup(STDOUT_FILENO);
	if (*saved_stdin == -1 || *saved_stdout == -1)
	{
		ft_putstr_fd("[ERROR] with the saved output or in \n", 2);
		return (-1);
	}
	return (0);
}

void	restore_fds(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		ft_putstr_fd("[ERROR] failed to restore stdin \n", 2);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		ft_putstr_fd("[ERROR] failed to restore stdout \n", 2);
	close(saved_stdin);
	close(saved_stdout);
}

void	close_fds(t_command *cmd)
{
	if (cmd->pipe_in_fd != -1)
		close(cmd->pipe_in_fd);
	if (cmd->pipe_out_fd != -1)
		close(cmd->pipe_out_fd);
}
