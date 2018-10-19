/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 12:41:05 by awajsbro          #+#    #+#             */
/*   Updated: 2018/10/17 16:22:21 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static char		is_faster(int sim, t_list **path, t_li *li)
{
	int		i;
	int		j;
	int		x;

	i = -1;
	while (++i < sim)
	{
		x = -1;
		while (li->way[++x] != NULL)
		{
			j = -1;
			while (li->way[x][++j] != 1 && ((int*)(path[i]->content))[j] != 1)
				if (((int*)(path[i]->content))[j] == li->way[x][j])
					return (1);
		}
	}
	return (0);
}

static char		is_cross(int sim, t_list **path, t_li *li)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = -1;
	while (++i < sim)
	{
		j = i;
		while (++j < sim)
		{
			x = 0;
			while (((int*)(path[i]->content))[++x] != 1)
			{
				y = 0;
				while (((int*)(path[j]->content))[++y] != 1)
					if (((int*)(path[i]->content))[x]
						== ((int*)(path[j]->content))[y]
							&& (x == y || li->lem > sim + 1))
						return (1);
			}
		}
	}
	return (0);
}

static char		is_work(t_list **path, int *sim, int *i, t_li *li)
{
	if (is_cross(*sim, path, li) == 1 || is_faster(*sim, path, li))
	{
		while ((--(*i) == *sim - 1)
			|| (*i >= 0 && path[*i]->next == path[*i + 1]))
			;
		if (*i == -1 && path[*sim - 1]->next == NULL)
		{
			(*sim)--;
			path[*sim] = NULL;
		}
		else
			li->lsp = path[*i + 1]->next;
	}
	else if ((path[*sim - 1]->size - path[0]->size) > li->lem - *sim)
	{
		(*sim)--;
		*i = -1;
	}
	else
		return (1);
	return (0);
}

static t_list	**select_path(int *sim, t_li *li, int i)
{
	t_list	**path;
	int		tmp;

	if (!(path = (t_list**)malloc(sizeof(*path) * *sim)))
		return (NULL);
	*path = NULL;
	tmp = *sim;
	li->lsp = ft_lststart(li->lsp);
	while ((*path == NULL || !is_work(path, sim, &i, li)) && *sim != 0)
	{
		if (tmp != *sim)
		{
			tmp = *sim;
			li->lsp = ft_lststart(li->lsp);
		}
		while (++i < *sim)
		{
			path[i] = li->lsp;
			if (li->lsp == NULL || li->lsp->next == NULL)
				break ;
			li->lsp = li->lsp->next;
		}
	}
	return (path);
}

void			choose_path(int sim, t_li *li)
{
	int		i;
	int		lem;
	t_list	**path;

	lem = 0;
	while ((((li->opt & INNOND) == INNOND)
		&& lem < li->lem && drown_room(li, 0))
			|| (((li->opt & INNOND) != INNOND) && lem < li->lem))
	{
		sim = li->lem - lem < sim ? li->lem - lem : sim;
		sim = (size_t)sim < ft_lstlen(li->lsp) ? sim : ft_lstlen(li->lsp);
		if (!(path = select_path(&sim, li, -1)))
		{
			delete_anthill(li->str, li);
			ft_putendl("ERROR with MALLOC");
			return ;
		}
		i = -1;
		while (++i < sim)
			li->way[lem++] = path[i]->content;
		move_ant(li, lem);
		free(path);
	}
	while (move_ant(li, lem))
		li->dlem = lem;
}
