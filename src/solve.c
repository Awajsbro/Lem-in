/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 12:41:05 by awajsbro          #+#    #+#             */
/*   Updated: 2018/07/26 15:27:51 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static char		move_ant(t_li *li, int lem)
{
	int		i;

	i = -1;
	if (lem > 0 && (li->way[lem - 1] == NULL || *(li->way[lem - 1]) != 1))
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
	i = -1;
	while (++i < lem)
		if (li->way[i][0] != 1 && move_ant(li, lem - 1))
			return (1);
	return (0);
}

static char		is_faster(int sim, t_list **path, t_li *li)
{
	int 	i;
	int 	j;
	int 	x;

	i = -1;
	while (++i < sim)
	{
		x = -1;
		while (li->way[++x] != NULL)
		{
			j = 0;
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
		while ((--(*i) == *sim - 1) || (*i >= 0 && path[*i]->next == path[*i + 1]))
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

void			choose_path(int sim, t_li *li)
{
	int		i;
	int		lem;
	t_list	**path;

	lem = 0;
	while ((((li->opt & INNOND) == INNOND) && lem < li->lem && drown_room(li, 0))
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
		;
	drown_room(li, 1);
	if ((li->opt & INNOND) == INNOND)
	{
		if (lem > ((2 * li->lem) / 3))
			ft_printf("\"%{ver}%d%{reset_true}\" fourmis on pu senfuire", lem);
		else if (lem > (li->lem / 3))
			ft_printf("\"%{jau}%d%{reset_true}\" fourmis on pu senfuire", lem);
		else
			ft_printf("\"%{rou}%d%{reset_true}\" fourmis on pu senfuire", lem);
		ft_printf(" sur \"%{ble}%{state_gras}%d%{reset_true}\"\n", li->lem);
	}
}
