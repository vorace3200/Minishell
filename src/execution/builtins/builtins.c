/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:26:09 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/19 14:41:18 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	execute_builtin_with_redir(t_shell *shell, t_command *cmd)
{
	int	saved_stdin;
	int	saved_stdout;

	if (save_std_fds(&saved_stdin, &saved_stdout) == -1)
		return (-1);
	if (redirect_fds(cmd) == -1)
	{
		ft_putstr_fd("[ERROR] Redirection failed. Please check. \n", 2);
		restore_fds(saved_stdin, saved_stdout);
		return (-1);
	}
	if (execute_builtin(shell, cmd))
		restore_fds(saved_stdin, saved_stdout);
	return (1);
}

int	is_builtin(char **args)
{
	if (!args || !args[0])
		return (0);
	if (ft_strcmp(args[0], "echo") == 0)
		return (1);
	if (ft_strcmp(args[0], "exit") == 0)
		return (1);
	if (ft_strcmp(args[0], "pwd") == 0)
		return (1);
	if (ft_strcmp(args[0], "cd") == 0)
		return (1);
	if (ft_strcmp(args[0], "export") == 0)
		return (1);
	if (ft_strcmp(args[0], "unset") == 0)
		return (1);
	if (ft_strcmp(args[0], "env") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_shell *shell, t_command *cmd)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		builtin_echo(shell, cmd->args, cmd->have_quote);
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		builtin_exit(shell, cmd->args);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		builtin_pwd(shell);
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		builtin_cd(shell, cmd->args);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		builtin_export(shell, cmd->args);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		builtin_unset(shell, cmd->args);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		builtin_env(shell);
	else
		return (0);
	return (1);
}
