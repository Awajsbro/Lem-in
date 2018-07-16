/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:55:47 by awajsbro          #+#    #+#             */
/*   Updated: 2018/07/16 12:36:20 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

/*
**static void		debug(t_list *lst, t_li *li)
**{
**	int i;
**
**	ft_putendl_fd("---------------------", 2);
**	lst = ft_lststart(lst);
**	while (lst != NULL)
**	{
**		i = -1;
**		ft_printf("%[fd2]%d --> ", lst->size, lst->content);
**		while (((int*)(lst->content))[++i] != 1 && i < lst->size)
**			ft_printf("%[fd2]%s, ", li->room[((int*)(lst->content))[i]]->name);
**		ft_printf("%[fd2]%s\n", li->room[((int*)(lst->content))[i]]->name);
**		lst = lst->next;
**	}
**	ft_putendl_fd("---------------------", 2);
**}
*/

static t_list	*order_path(t_list *lsp)
{
	int		len;
	t_list	*tmp;

	len = lsp->size;
	tmp = lsp->next;
	while (tmp != NULL)
	{
		if (len > tmp->size)
			len = tmp->size;
		tmp = tmp->next;
	}
	ft_lstfindsize(&lsp, len);
	tmp = ft_lstremove(&lsp);
	while (lsp != NULL)
	{
		while (lsp != NULL && ft_lstfindsize(&lsp, len))
			ft_lstaddend(&tmp, ft_lstremove(&lsp));
		len++;
	}
	return (tmp);
}

static int		*cpy_view(int *view, int len)
{
	int		*cpy;

	if (!(cpy = (int*)malloc(sizeof(*cpy) * (len + 1))))
		return (NULL);
	*cpy = 0;
	while (len > 0)
	{
		cpy[len] = view[len];
		len--;
	}
	return (cpy);
}

static char		good_room(int r1, int r2, int *view, t_li *li)
{
	int		i;

	i = -1;
	while (++i < li->npipe)
	{
		if ((li->pip[i][0] == r1 && li->pip[i][1] == r2)
			|| (li->pip[i][1] == r1 && li->pip[i][0] == r2))
			break ;
	}
	if (i == li->npipe)
		return (0);
	if (view == NULL)
		return (1);
	while (*(--view) != 0)
		if (*view == r2)
			return (0);
	return (1);
}

static char		set_path(int r, int *view, t_list **lsp, t_li *li)
{
	int		i;
	t_list	*tmp;

	i = 0;
	*view = r;
	if (r == 1)
	{
		i++;
		while (*(--view) != 0)
			i++;
		if (!(tmp = ft_lstnew(cpy_view(view, i), i)) || !(tmp->content))
			return (-1);
		if (*lsp == NULL)
			*lsp = tmp;
		else
			ft_lstaddend(lsp, tmp);
	}
	else
		while (++i < li->nroom)
			if (good_room(r, i, view, li))
				if (set_path(i, view + 1, lsp, li) == -1)
					return (-1);
	return (1);
}

char			path_finding(t_li *li)
{
	int		view[li->nroom];
	int		i;

	i = 0;
	*view = 0;
	while (++i < li->nroom)
		if (good_room(0, i, NULL, li))
			if (set_path(i, view + 1, &li->lsp, li) == -1)
				return (0);
	if (li->lsp == NULL)
		return (0);
	li->lsp = order_path(ft_lststart(li->lsp));
	return (1);
}
