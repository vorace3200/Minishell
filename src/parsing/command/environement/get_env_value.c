/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 22:31:30 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/18 16:02:27 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../Minishell.h"

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

char	*find_command_in_path(const char *cmd, const char *path)
{
	char	**dirs;
	char	*cmd_path;
	int		i;

	dirs = ft_split((char *)path, ':');
	if (!dirs)
		return (NULL);
	i = 0;
	while (dirs[i])
	{
		cmd_path = ft_strjoin(dirs[i], "/");
		cmd_path = ft_strjoin_free(cmd_path, (char *)cmd);
		if (!access(cmd_path, X_OK))
		{
			ft_free_split(dirs);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	ft_free_split(dirs);
	return (NULL);
}
