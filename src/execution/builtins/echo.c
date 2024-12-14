/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 16:27:04 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:10:26 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell_exec.h"

char	*remove_slash(const char *str)
{
	char	*result;

	int i, j;
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] && str[i + 1] != '\\')
			i++;
		result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
}

void	builtin_echo(char **args)
{
	int		i;
	int		newline;
	char	*str;

	newline = 1;
	i = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}
	while (args[i])
	{
		str = remove_slash(args[i]);
		if (str)
		{
			printf("%s", str);
			free(str);
		}
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
}
