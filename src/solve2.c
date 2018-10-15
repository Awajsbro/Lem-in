/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/14 19:03:08 by awajsbro          #+#    #+#             */
/*   Updated: 2018/10/14 19:05:22 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

char		move_ant(t_li *li, int lem)
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
