/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:38:15 by gada-sil          #+#    #+#             */
/*   Updated: 2024/10/07 14:38:17 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	i;
	t_list	*temp;

	i = 0;
	if (lst == NULL)
		return (0);
	temp = lst;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
/*#include <stdio.h>
int    main()
{
	int l = 5;
	t_list	*lst = ft_lstnew(&l);
	t_list	*node1;
	t_list	*node2;
	t_list	*node3;
	int size = 0;
	int i = 10;
	int j = 20;
	int k = 30;

	node1 = ft_lstnew(&i);
	node2 = ft_lstnew(&j);
	node3 = ft_lstnew(&k);

	ft_lstadd_back(&lst, node1);
	ft_lstadd_back(&lst, node2);
	ft_lstadd_back(&lst, node3);

	size = ft_lstsize(lst);

	printf("%d", size);
}*/
