/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:56:36 by vorace32          #+#    #+#             */
/*   Updated: 2024/11/04 15:38:25 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell_exec.h"

void	execute_command(t_command *cmd)
{
	if (cmd->redir_in != -1)
	{
		dup2(cmd->redir_in, STDIN_FILENO);
		close(cmd->redir_in);
	}
	else if (cmd->pipe_in_fd != -1)
	{
		dup2(cmd->pipe_in_fd, STDIN_FILENO);
		close(cmd->pipe_in_fd);
	}
	if (cmd->redir_out != -1)
	{
		dup2(cmd->redir_out, STDOUT_FILENO);
		close(cmd->redir_out);
	}
	else if (cmd->pipe_out_fd != -1)
	{
		dup2(cmd->pipe_out_fd, STDOUT_FILENO);
		close(cmd->pipe_out_fd);
	}
	if (execvp(cmd->args[0], cmd->args) == -1)
	{
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

void	execute_commands(t_shell *shell)
{
	t_command	*cmd;
	int			pipefd[2];
	pid_t		pid;
	int			status;

	cmd = shell->cmd_list;
	while (cmd)
	{
		if (cmd->pipe_out)
		{
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}
			cmd->pipe_out_fd = pipefd[1];
			if (cmd->next)
			{
				cmd->next->pipe_in_fd = pipefd[0];
			}
			else
			{
				close(pipefd[0]);
			}
		}
		else
		{
			cmd->pipe_out_fd = -1;
		}
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (cmd->pipe_in_fd != -1)
			{
				dup2(cmd->pipe_in_fd, STDIN_FILENO);
				close(cmd->pipe_in_fd);
			}
			if (cmd->pipe_out_fd != -1)
			{
				dup2(cmd->pipe_out_fd, STDOUT_FILENO);
				close(cmd->pipe_out_fd);
			}
			if (cmd->pipe_in_fd != -1)
				close(cmd->pipe_in_fd);
			if (cmd->pipe_out_fd != -1)
				close(cmd->pipe_out_fd);
			execute_command(cmd);
			exit(EXIT_FAILURE);
		}
		else
		{
			if (cmd->pipe_in_fd != -1)
				close(cmd->pipe_in_fd);
			if (cmd->pipe_out_fd != -1)
				close(cmd->pipe_out_fd);
		}
		cmd = cmd->next;
	}
	while ((pid = wait(&status)) > 0)
		;
}
