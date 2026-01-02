/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:10:42 by gada-sil          #+#    #+#             */
/*   Updated: 2024/10/09 16:10:43 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;

	if (!*lst || !del)
		return ;
	while (*lst)
	{
		aux = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = aux;
	}
	*lst = NULL;
}

/*void	del(void *content)
{
	free(content);
}

#include <stdio.h>
int    main()
{
	int    i = 42;
	int    k = 56;
	int    j = 10;
	t_list *head = ft_lstnew(&i);

	t_list *node = ft_lstnew(&k);

	head->next = ft_lstnew(&j);
	ft_lstadd_back(&head, node);
	printf("%d\n", *(int *)head->content);
	printf("%d\n", *(int *)head->next->content);
	printf("%d\n", *(int *)head->next->next->content);
	
	ft_lstclear(&head, del);

	printf("%d\n", *(int *)head->content);
	printf("%d\n", *(int *)head->next->content);
	printf("%d\n", *(int *)head->next->next->content);
}*/
