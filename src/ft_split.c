/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:50:44 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/28 03:21:32 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i] != c && str[i])
			&& (str[i + 1] == c || str[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	fill_word(char *dest, const char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

static void	jump_apex(int *i, const char *str, char **split, int word)
{
	int		len;
	char	c;

	len = 0;
	c = str[*i];
	(*i)++;
	while (str[(*i) + len] != c && str[(*i) + len])
		len++;
	split[word] = (char *) malloc(sizeof(char) * (len + 1));
	if (!split[word])
		return (free_arr(split));
	fill_word(split[word++], &str[*i], len);
	(*i) += len + 1;
}

static int	fill_split_v2(char **split, const char *str, char c)
{
	int	word;
	int	i;
	int	len;

	word = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c || str[i] == '\0')
			i++;
		else if (str[i] == '\'' || str[i] == '\"')
			jump_apex(&i, str, split, word++);
		else
		{
			len = 1;
			while (str[i + len] != c && str[i + len])
				len++;
			split[word] = (char *) malloc(sizeof(char) * (len + 1));
			if (!split[word])
				return (free_arr(split), 0);
			fill_word(split[word++], &str[i], len);
			i += len;
		}
	}
	return (1);
}

char	**ft_split_v2(const char *str, char c)
{
	char	**split;
	int		words;

	if (!str)
		return (NULL);
	words = count_words(str, c);
	split = (char **) malloc(sizeof(char *) * (words + 1));
	if (!split)
		return (NULL);
	split[words] = NULL;
	if (!fill_split_v2(split, str, c))
	{
		free(split);
		split = NULL;
	}
	return (split);
}
