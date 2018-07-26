/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:31:13 by awajsbro          #+#    #+#             */
/*   Updated: 2018/07/25 15:12:07 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

char		drown_room(t_li *li, char end)
{
	static t_list	*uw = NULL;
	static int		lv = 0;
	t_list			*tmp;
	int				i;

	i = -1;
	tmp = ft_lststart(li->lsp);
	if (end == 1)
		ft_lstaddstart(&li->lsp, ft_lstend(uw));
	else
		while (tmp != NULL)
		{
			while (++i < tmp->size)
				if (li->room[((int*)(tmp->content))[i]]->y < lv + i)
				{
					if (tmp == li->lsp)
						li->lsp = tmp->prev == NULL ? tmp->next : tmp->prev;
					ft_lstaddend(&uw, ft_lstremove(&tmp));
					i = -42;
					break ;
				}
			if (i != -42 && tmp != NULL)
				tmp = tmp->next;
			i = -1;
		}
	lv++;
	return (li->lsp == NULL ? 0 : 1);
}

void		debug(t_list *lst, t_li *li)
{
	int i;

	ft_putendl_fd("---------------------", 2);
	lst = ft_lststart(lst);
	while (lst != NULL)
	{
		i = -1;
		ft_printf("%[fd2]%d --> ", lst->size, lst->content);
		while (((int*)(lst->content))[++i] != 1 && i < lst->size)
			ft_printf("%[fd2]%s, ", li->room[((int*)(lst->content))[i]]->name);
		ft_printf("%[fd2]%s\n", li->room[((int*)(lst->content))[i]]->name);
		lst = lst->next;
	}
	ft_putendl_fd("---------------------\n", 2);
}
