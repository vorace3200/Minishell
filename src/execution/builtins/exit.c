/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:27:25 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:22:05 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	signe;
	int	i;

	i = 0;
	result = 0;
	signe = 1;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		signe = -signe;
		i++;
	}
	else if (nptr[i] == '+')
	{
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - 48);
		i++;
	}
	return (result * signe);
}

void	free_ressouces(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->env)
	{
		while (shell->env[i])
			free(shell->env[i++]);
		free(shell->env);
	}
	if (shell->cmd_list)
		free_commands(shell->cmd_list);
	if (shell->input)
		free(shell->input);
}

void	builtin_exit(t_shell *shell, char **args)
{
	int	status;

	status = 0;
	shell->is_running = 0;
	if (args[1] && args[2])
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell->exit_status = 1;
		return ;
	}
	if (args[1])
		status = ft_atoi(args[1]);
	else
		status = shell->exit_status;
	free_ressouces(shell);
	exit(status);
}
