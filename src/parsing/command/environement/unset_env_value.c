/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:35:34 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:22:30 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

static int	find_env_index(t_shell *shell, const char *env_name)
{
	int	i;
	int	len;

	if (!shell->env || !env_name)
		return (-1);
	len = ft_strlen(env_name);
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], env_name, len)
			&& shell->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static int	rebuild_env(t_shell *shell, int remove_index)
{
	int		size;
	int		j;
	char	**new_env;
	int		i;

	size = env_count(shell->env);
	new_env = malloc(sizeof(char *) * size);
	if (!new_env)
		return (1);
	j = 0;
	i = 0;
	while (shell->env[i])
	{
		if (i != remove_index)
			new_env[j++] = shell->env[i];
		else
			free(shell->env[i]);
		i++;
	}
	new_env[j] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

int	unset_env_value(t_shell *shell, const char *env_name)
{
	int	index;

	index = find_env_index(shell, env_name);
	if (index == -1)
		return (0);
	return (rebuild_env(shell, index));
}
