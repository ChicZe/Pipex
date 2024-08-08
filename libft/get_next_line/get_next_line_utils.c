/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:08:35 by ciusca            #+#    #+#             */
/*   Updated: 2024/04/05 16:58:56 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strchr(const char *s, int c)
{
	while ((unsigned char)*s != (unsigned char)c && *s)
		s++;
	if (*s == '\0' && (unsigned char)c != '\0')
		return (NULL);
	return ((char *)s);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	i = -1;
	if ((int)start > (int)ft_strlen(s))
	{
		substr = malloc(sizeof(char) * 1);
		if (substr == NULL)
			return (NULL);
		*substr = '\0';
		return (substr);
	}
	s += start;
	if ((int)ft_strlen(s) <= (int)len)
		substr = malloc(sizeof(char) * (ft_strlen(s) + 1));
	else
		substr = malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	while (s[++i] != '\0' && i < len)
		substr[i] = s[i];
	substr[i] = '\0';
	return (substr);
}
