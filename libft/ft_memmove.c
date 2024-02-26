/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 21:10:30 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/01/11 17:20:29 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	unsigned char	*castdest;
	unsigned char	*castsrc;

	if (!dest && !src)
		return (NULL);
	castdest = (unsigned char *) dest;
	castsrc = (unsigned char *) src;
	if (dest < src)
		ft_memcpy(dest, src, len);
	else
	{
		while (len > 0)
		{
			castdest[len - 1] = castsrc[len - 1];
			len--;
		}
	}
	return (dest);
}
