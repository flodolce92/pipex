/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 00:32:41 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/01/17 15:57:41 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	srclen;

	srclen = ft_strlen(src);
	dup = (char *) malloc(sizeof(char) * srclen + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, src, srclen + 1);
	return (dup);
}
