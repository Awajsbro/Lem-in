/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:18:47 by awajsbro          #+#    #+#             */
/*   Updated: 2018/10/16 15:49:45 by awajsbro         ###   ########.fr       */
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
	li->opt = 0;
	li->lem = 0;
	li->dlem = 0;
	li->nroom = 0;
	li->npipe = 0;
}

static char	option(int ac, char **av)
{
	char	opt;

	opt = 0;
	while (--ac > 0)
		if (ft_strequ(av[ac], "-p"))
			opt = (opt | AFFPATH);
		else if (ft_strequ(av[ac], "-i"))
			opt = (opt | INNOND);
	return (opt);
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
	drown_room(li, 1);
}

static char	main_after_read(char *str, char opt)
{
	t_li	li;

	init_li(&li);
	li.opt = opt;
	li.str = str;
	if (!(init_anthill(str, &li, NULL)) || (!path_finding(&li)))
	{
		delete_anthill(str, &li);
		ft_putendl("ERROR");
		return (0);
	}
	ft_putendl(str);
	if ((li.opt & AFFPATH) == AFFPATH)
		debug(li.lsp, &li);
	if ((li.opt & INNOND) == INNOND)
		ft_printf("%{ble} Water%{reset_true} is comming !\n");
	init_move(&li);
	delete_anthill(str, &li);
	return (0);
}

int			main(int ac, char **av)
{
	char	buff[128];
	char	*str;
	int		r;

	str = ft_strnew(0);
	while ((r = read(0, buff, 127)) > 0)
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
	str = ft_joinnfree(str, "\n", 1);
	return (main_after_read(str, option(ac, av)));
}
