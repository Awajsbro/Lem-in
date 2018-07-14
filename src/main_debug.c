/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:00:22 by awajsbro          #+#    #+#             */
/*   Updated: 2018/07/14 16:12:01 by awajsbro         ###   ########.fr       */
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

int			main(void)
{
	char	buff[128];
	char	*str;
	int		r;
	t_li	li;
	int fd;

	init_li(&li);
	str = ft_strnew(0);
	fd = open("/Users/awajsbro/project/test_lem/lem-in_maps/valid_maps_part_1_trace/100_map_trace", O_RDONLY);
	while ((r = read(fd, buff, 127)) > 0)
	{
		buff[r] = 0;
		if (!(str = ft_joinnfree(str, buff, 1)))
			ft_putendl("ERROR with MALLOC");
	}
	if (r == -1)
	{
		ft_strdel(&str);
		ft_putendl("ERROR with READ");
		return (0);
	}
	li.str = str;
	if (!(init_anthill(str, &li)) || (!path_finding(&li)))
	{
		delete_anthill(str, &li);
		ft_putendl("ERROR");
		return (0);
	}
	ft_putendl(str);
	choose_path(&li);
	delete_anthill(str, &li);
	return (0);
}
