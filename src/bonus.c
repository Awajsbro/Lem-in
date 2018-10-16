/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 14:31:13 by awajsbro          #+#    #+#             */
/*   Updated: 2018/10/15 14:20:21 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void	ft_aff_survive(t_li *li)
{
	if (li->dlem > ((2 * li->lem) / 3))
		ft_printf("\"%{ver}%d%{reset_true}\" fourmis on pu senfuire", li->dlem);
	else if (li->dlem > (li->lem / 3))
		ft_printf("\"%{jau}%d%{reset_true}\" fourmis on pu senfuire", li->dlem);
	else
		ft_printf("\"%{rou}%d%{reset_true}\" fourmis on pu senfuire", li->dlem);
	ft_printf(" sur \"%{ble}%{state_gras}%d%{reset_true}\"\n", li->lem);
}

static char	fuck_norme(t_li *li, t_list **uw)
{
	static int		lv = 0;
	t_list			*tmp;
	int				i;

	i = -1;
	tmp = ft_lststart(li->lsp);
	while (tmp != NULL)
	{
		while (++i < tmp->size + 1)
			if (li->room[((int*)(tmp->content))[i]]->y < lv + i)
			{
				if (tmp == li->lsp)
					li->lsp = tmp->prev == NULL ? tmp->next : tmp->prev;
				ft_lstaddend(uw, ft_lstremove(&tmp));
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
//benoit est pd
char		drown_room(t_li *li, char end)
{
	static t_list	*uw = NULL;
	char			r;

	r = 0;
	if (end == 1)
	{
		ft_lstaddstart(&li->lsp, ft_lstend(uw));
		if ((li->opt & INNOND) == INNOND)
			ft_aff_survive(li);
	}
	else
		r = fuck_norme(li, &uw);
	return (r);
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
