/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finding.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 16:55:47 by awajsbro          #+#    #+#             */
/*   Updated: 2018/06/01 19:55:39 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static char	is_view(int room, int* view)
{
	while (*(--view) != 0)
		if (*view == room)
			return (1);
	return (0);
}

static char	is_link(int r1, int r2, t_li *li)
{
	int		i;

	i = -1;
	while (++i < li->npipe)
	{
		if ((li->pip[i][0] == r1 && li->pip[i][1] == r2)
			|| (li->pip[i][1] == r1 && li->pip[i][0] == r2))
			return (1);
	}
	return (0);
}

static void	set_path(int r, int *view, t_list **lsp, t_li *li)
{
	int		i;
	int		len;

	i = 0;
	len = 1;
	*view = r;
	while (++i < li->nroom)
		if (is_link(r, i, li) && !is_view(i, view))
		{
			if (i == 1)
			{
				while (*(--view) != 0)
					len++;
				if (*lsp == NULL)
					*lsp = ft_lstnew(ft_memcpy(
						ft_memalloc(len), view, len * sizeof(*view)), len);
				else
					ft_lstaddend(lsp, ft_lstnew(ft_memcpy(
						ft_memalloc(len), view, len * sizeof(*view)), len));
			}
			else
				set_path(i, view + 1, lsp, li);
		}
}

char	path_finding(t_li *li)
{
	t_list	*lsp;
	int		view[li->nroom];
	int		i;

	i = 0;
	*view = 0;
	lsp = NULL;
	while (++i < li->nroom)
		if (is_link(0, i, li))
			set_path(i, view + 1, &lsp, li);
	if (lsp == NULL)
		return (0);
	// order_path();
	return(1);
}
