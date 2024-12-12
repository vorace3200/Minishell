/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:31:30 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/12 23:15:53 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell_exec.h"

char	*get_env_value(t_shell *shell, char *env_name)
{
	int		i;
	size_t	name;

	if (!shell->env || !env_name)
		return (NULL);
	name = ft_strlen(env_name);
	i = 0;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], env_name, name)
			&& shell->env[i][name] == '=')
			return (shell->env[i] + name + 1);
		i++;
	}
	return (NULL);
}
