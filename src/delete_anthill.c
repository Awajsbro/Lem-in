/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_anthill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 18:07:50 by awajsbro          #+#    #+#             */
/*   Updated: 2018/07/13 11:53:55 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	delete_path(t_list *lsp)
{
	t_list *tmp;

	lsp = ft_lststart(lsp);
	while (lsp != NULL)
	{
		tmp = lsp->next;
		while (lsp->size-- > -1)
			((int*)(lsp->content))[lsp->size + 1] = 0;
		lsp->size = 0;
		free(lsp->content);
		lsp->content = NULL;
		lsp->next = NULL;
		lsp->prev = NULL;
		free(lsp);
		lsp = tmp;
	}
}

void	delete_pipe(t_li *li)
{
	while ((li->npipe)--)
	{
		li->pip[li->npipe][0] = 0;
		li->pip[li->npipe][1] = 0;
		free(li->pip[li->npipe]);
	}
	free(li->pip);
	li->npipe = 0;
}

void	delete_anthill(char *s, t_li *li)
{
	li->lem = 0;
	li->str = NULL;
	li->beg = NULL;
	li->end = NULL;
	if (s != NULL)
		ft_strdel(&s);
	if (ROOM != NULL && ROOM[0] != NULL)
		while ((li->nroom)--)
			ft_ptdel(&(ROOM[li->nroom]));
	li->nroom = 0;
	free(ROOM);
	ROOM = NULL;
	if (li->pip != NULL)
		delete_pipe(li);
	li->pip = NULL;
	if (li->lsp != NULL)
		delete_path(li->lsp);
	li->lsp = NULL;
	if (li->way != NULL)
		free(li->way);
	li->way = NULL;
	li = NULL;
}
