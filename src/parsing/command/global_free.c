/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:42:35 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/19 16:14:43 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

void	free_commands(t_command *cmd_list)
{
	t_command	*tmp;
	int			i;

	while (cmd_list)
	{
		tmp = cmd_list;
		cmd_list = cmd_list->next;
		i = 0;
		while (tmp->args && tmp->args[i])
		{
			free(tmp->args[i]);
			i++;
		}
		free(tmp->args);
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		if (tmp->redir_in != -1)
			close(tmp->redir_in);
		if (tmp->redir_out != -1)
			close(tmp->redir_out);
		free(tmp);
	}
}

void	clean_up(char **env)
{
	unsigned int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	free_env(t_shell *shell)
{
	rl_clear_history();
	if (shell->cmd_list)
	{
		free_commands(shell->cmd_list);
		shell->cmd_list = NULL;
	}
	if (shell->env)
	{
		clean_up(shell->env);
		shell->env = NULL;
	}
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
}

void	handle_execve_error(t_shell *shell, char *cmd)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	cleanup_command_list(shell);
	exit(127);
}
