/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_anthill.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 18:07:50 by awajsbro          #+#    #+#             */
/*   Updated: 2018/05/30 17:51:34 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

void	delete_anthill(char *s, t_li *li)
{
	li->lem = 0;
	li->beg = NULL;
	li->end = NULL;
	if (s != NULL)
		ft_strdel(&s);
	if (li->room[0] != NULL)
		while ((li->nroom)--)
			ft_ptdel(&(li->room[li->nroom]));
	li->nroom = 0;
	free(li->room);
	li->room = NULL;
	// if (li->way != NULL)
	// 	while (je sais pas quoi)
	// 	{
	// 		while (i > 0)
	// 			li->way[truc][i] = 0;
	// 		free(li->way[truc]);
	// 	}
	// free(li->way); // ajout pip et npipe
}
