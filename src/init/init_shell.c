/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 00:35:18 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/18 14:11:33 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Minishell.h"

char	**copy_env(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	while (env[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			while (i > 0)
				free(new_env[--i]);
			free(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

void	init_shell(t_shell *shell, char **env)
{
	shell->env = copy_env(env);
	shell->input = NULL;
	shell->cmd_list = NULL;
	shell->exit_status = 0;
	shell->is_running = 0;
	shell->have_pipe = 0;
}
