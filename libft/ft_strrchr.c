/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 03:18:17 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/01/17 16:04:51 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int		i;
	char	*caststr;
	char	*temp;

	i = 0;
	temp = NULL;
	caststr = (char *) str;
	while (caststr[i])
	{
		if (caststr[i] == (char) ch)
			temp = &caststr[i];
		i++;
	}
	if (caststr[i] == (char) ch)
		temp = &caststr[i];
	return (temp);
}
