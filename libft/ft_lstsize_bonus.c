/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 16:00:09 by ciusca            #+#    #+#             */
/*   Updated: 2024/03/04 17:00:20 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	n;

	if (lst == NULL)
		return (0);
	n = 1;
	while (lst->next != NULL)
	{
		lst = lst->next;
		n++;
	}
	return (n);
}
