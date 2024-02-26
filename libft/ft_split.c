/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 00:37:59 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/26 09:49:30 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

void	del_split(char **split)
{
	int	word;

	word = 0;
	while (split[word])
	{
		free(split[word]);
		split[word] = NULL;
		word++;
	}
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

static int	fill_split(char **split, const char *str, char c)
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
		else
		{
			len = 1;
			while (str[i + len] != c && str[i + len])
				len++;
			split[word] = (char *) malloc(sizeof(char) * (len + 1));
			if (!split[word])
				return (del_split(split), 0);
			fill_word(split[word], &str[i], len);
			i += len;
			word++;
		}
	}
	return (1);
}

char	**ft_split(const char *str, char c)
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
	if (!fill_split(split, str, c))
	{
		free(split);
		split = NULL;
	}
	return (split);
}
