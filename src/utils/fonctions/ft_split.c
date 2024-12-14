/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vorace32 <vorace32000@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:08:52 by vorace32          #+#    #+#             */
/*   Updated: 2024/12/14 14:23:06 by vorace32         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Minishell.h"

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

int	word_count(char *str, char delimiter)
{
	int	i;
	int	wc;

	i = 0;
	wc = 0;
	while (str[i])
	{
		while (str[i] && str[i] == delimiter)
			i++;
		if (str[i])
			wc++;
		while (str[i] && str[i] != delimiter)
			i++;
	}
	return (wc);
}

char	*create_word(char *str, int start, int end)
{
	char	*word;

	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	ft_strncpy(word, str + start, end - start);
	return (word);
}

char	**ft_split(char *str, char delimiter)
{
	int		i;
	int		start;
	int		k;
	char	**out;

	i = 0;
	k = 0;
	out = (char **)malloc(sizeof(char *) * (word_count(str, delimiter) + 1));
	if (!out)
		return (NULL);
	while (str[i])
	{
		while (str[i] && str[i] == delimiter)
			i++;
		start = i;
		while (str[i] && str[i] != delimiter)
			i++;
		if (i > start)
			out[k++] = create_word(str, start, i);
	}
	out[k] = NULL;
	return (out);
}
