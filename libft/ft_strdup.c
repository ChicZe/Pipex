/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 17:36:45 by ciusca            #+#    #+#             */
/*   Updated: 2024/03/01 15:21:28 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*dup;
	int		i;

	i = 0;
	len = ft_strlen(s);
	dup = (char *) malloc (sizeof(char) * len + 1);
	if (!dup)
		return (NULL);
	while (*s)
		dup[i++] = *s++;
	dup[i] = 0;
	return (dup);
}
