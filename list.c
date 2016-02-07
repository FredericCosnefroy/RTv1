/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcosnefr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 18:49:44 by fcosnefr          #+#    #+#             */
/*   Updated: 2016/02/07 18:49:45 by fcosnefr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RTv1.h"

t_list			*lstnew(const void *data, unsigned int size)
{
	t_list			*lst;

	if (!(lst = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!(lst->data = malloc(size)))
		return (NULL);
	memcpy(lst->data, data, size);
	lst->size = (data == NULL) ? 0 : size;
	lst->next = NULL;
	return (lst);
}

t_list			*lstadd(t_list **lst, const void *data, unsigned int size)
{
	t_list *node;
	t_list *tmp;

	node = lstnew(data, size);
	if (!node || !lst)
		return (NULL);
	if (!*lst)
	{
		*lst = node;
		return (*lst);
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (*lst);
}
