/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 12:41:05 by awajsbro          #+#    #+#             */
/*   Updated: 2018/07/14 18:00:56 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static char		move_ant(t_li *li, int lem)
{
	int		i;

	i = -1;
	if (li->way[li->lem - 1] == NULL || *(li->way[li->lem - 1]) != 1)
	{
		while (++i < lem)
			if (li->way[i] != NULL && li->way[i][0] != 1)
			{
				++(li->way[i]);
				ft_printf("L%d-%s", i + 1, li->room[*(li->way[i])]->name);
				if (i + 1 < li->lem && li->way[i + 1] != NULL)
					ft_putchar(' ');
			}
		ft_putchar('\n');
		return (1);
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
	if (is_cross(*sim, path, li) == 1)
	{
		while ((--(*i) >= 0 && path[*i]->next == path[*i + 1])
			|| *i == *sim - 1)
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

static t_list	**select_path(int *sim, t_li *li)
{
	t_list	**path;
	int		i;
	int		tmp;

	i = -1;
	if (!(path = (t_list**)malloc(sizeof(*path) * *sim)))
		return (NULL);
	*path = NULL;
	tmp = *sim;
	li->lsp = ft_lststart(li->lsp);
	while (*path == NULL || !is_work(path, sim, &i, li))
	{
		if (tmp != *sim)
		{
			tmp = *sim;
			li->lsp = ft_lststart(li->lsp);
		}
		while (++i < *sim)
		{
			path[i] = li->lsp;
			if (li->lsp->next == NULL)
				break ;
			li->lsp = li->lsp->next;
		}
	}
	return (path);
}

void			choose_path(t_li *li)
{
	int		sim;
	int		lem;
	int		i;
	t_list	**path;

	i = -1;
	lem = li->lem;
	if (!(li->way = (int**)malloc(sizeof(*(li->way)) * li->lem)))
	{
		delete_anthill(li->str, li);
		ft_putendl("ERROR with MALLOC");
		return ;
	}
	while (++i < li->lem)
		li->way[i] = NULL;
	i = 0;
	while (lem > 0)
	{
		sim = ft_lstlen(li->lsp);
		sim = lem < sim ? lem : sim;
		sim = ROOM[0]->z > sim ? sim : ROOM[0]->z;
		if (!(path = select_path(&sim, li)))
		{
			delete_anthill(li->str, li);
			ft_putendl("ERROR with MALLOC");
			return ;
		}
		lem = lem - sim;
		sim = 0;
		while (lem + i < li->lem)
		{
			li->way[i] = path[sim]->content;
			i++;
			sim++;
		}
		move_ant(li, i);
		free(path);
	}
	while (move_ant(li, i))
		;
}
