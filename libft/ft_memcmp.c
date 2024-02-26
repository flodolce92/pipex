/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:05:43 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/01/11 17:09:41 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t n)
{
	size_t			i;
	unsigned char	*castptr1;
	unsigned char	*castptr2;

	i = 0;
	if (n == 0)
		return (0);
	castptr1 = (unsigned char *) ptr1;
	castptr2 = (unsigned char *) ptr2;
	while (castptr1[i] == castptr2[i] && i < n - 1)
		i++;
	return (castptr1[i] - castptr2[i]);
}
