/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:19:26 by awajsbro          #+#    #+#             */
/*   Updated: 2018/05/30 15:49:30 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

char		check_room(char **s, t_li *li)
{
	char	space;

	while (**s != 0)
	{
		(*s)++;
		space = 0;
		is_comment(s);
		if (is_order(s, li) == 0)
			return (0);
		while (**s != '\n' && **s != 0)
		{
			if ((**s == ' ' || **s == 'L') && (*s)[-1] == '\n')
				return (0);
			else if (**s == ' ')
				space++;
			else if (**s == '-')
				return (1);
			else if ((space > 0 && ft_isdigit(**s) == 0)
				|| ft_isprint(**s) == 0)
				return (0);
			(*s)++;
		}
		if (space != 2)
			return(0);
		if (++(li->nroom) > INT_MAX)
			return (0);
	}
	return (1);
}

static void	set_end_begin(int j, t_li *li)
{
	while (--j >= 0)
	{
		if (ft_strnequ(li->room[j]->name, li->beg, ft_strlen(li->room[j]->name)))
		{
			li->beg = NULL;
			ft_swap((void*)&li->room[j], (void*)&li->room[0]);
		}
		if (ft_strnequ(li->room[j]->name, li->end, ft_strlen(li->room[j]->name)))
		{
			li->end = NULL;
			ft_swap((void*)&li->room[j], (void*)&li->room[1]);
		}
	}
}

static char	check_duplicate(t_li *li)
{
	int		i;
	int		j;

	i = -1;
	while (++i < li->nroom - 1)
	{
		j = i;
		while (++j < li->nroom)
			if (ft_strequ(li->room[i]->name, li->room[j]->name) == 1
				|| (li->room[i]->x == li->room[j]->x
					&& li->room[i]->y == li->room[j]->y))
				return (0);
	}
	return (1);
}

char save_room(char *s, char *end, t_li *li)
{
	int		j;
	int		len;

	if (!(li->room = (t_pt**)malloc(sizeof(li->room) * li->nroom)))
		return (0);
	j = 0;
	while (s != end)
	{
		while (*s == '#')
			s = s + ft_strclen(s, '\n') + 1;
		len = ft_strclen(s, ' ');
		if (!(li->room[j] = ft_ptnew(ft_strndup(s, len), 0, 0, 0)))
			return (0);
		s = s + len + 1;
		li->room[j]->x = ft_atoi(s);
		s = s + ft_strclen(s, ' ');
		li->room[j]->y = ft_atoi(s);
		s = s + ft_strclen(s, '\n') + 1;
		j++;
	}
	set_end_begin(j, li);
	if (check_duplicate(li) == 0)
		return (0);
	return (1);
}
