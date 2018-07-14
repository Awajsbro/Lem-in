/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:18:47 by awajsbro          #+#    #+#             */
/*   Updated: 2018/07/13 11:51:39 by awajsbro         ###   ########.fr       */
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

	init_li(&li);
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
