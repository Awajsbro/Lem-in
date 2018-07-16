/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:00:22 by awajsbro          #+#    #+#             */
/*   Updated: 2018/07/16 16:36:50 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"
static void	init_li(t_li *li)
{
	li->str = NULL;
	li->beg = NULL;
	li->end = NULL;
	li->room = NULL;
	li->pip = NULL;
	li->lsp = NULL;
	li->way = NULL;
	li->lem = 0;
	li->nroom = 0;
	li->npipe = 0;
}

static void	init_move(t_li *li)
{
	int		sim;
	int		i;

	i = -1;
	if (!(li->way = (int**)malloc(sizeof(*(li->way)) * li->lem)))
	{
		delete_anthill(li->str, li);
		ft_putendl("ERROR with MALLOC");
		return ;
	}
	while (++i < li->lem)
		li->way[i] = NULL;
	sim = ft_lstlen(li->lsp);
	sim = ROOM[0]->z > sim ? sim : ROOM[0]->z;
	choose_path(sim, li);
}

static char	main_after_read(char *str)
{
	t_li	li;

	init_li(&li);
	li.str = str;
	if (!(init_anthill(str, &li)) || (!path_finding(&li)))
	{
		delete_anthill(str, &li);
		ft_putendl("ERROR");
		return (0);
	}
	ft_putendl(str);
	init_move(&li);
	delete_anthill(str, &li);
	return (0);
}

int			main(void)
{
	char	buff[128];
	char	*str;
	int		r;
	int		fd;

	str = ft_strnew(0);
	fd = open("/Users/awajsbro/project/lem_in/anthill/sujet0.txt", O_RDONLY);
	while ((r = read(fd, buff, 127)) > 0)
	{
		buff[r] = 0;
		if (!(str = ft_joinnfree(str, buff, 1)))
		{
			ft_putendl("ERROR with MALLOC");
			return (0);
		}
	}
	if (r == -1)
	{
		ft_strdel(&str);
		ft_putendl("ERROR with READ");
		return (0);
	}
	return (main_after_read(str));
}
