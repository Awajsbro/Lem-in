/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:19:26 by awajsbro          #+#    #+#             */
/*   Updated: 2018/10/15 13:55:24 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static char	real_check(char **s, char *space, char *minus)
{
	while (**s != '\n' && **s != 0)
	{
		if ((**s == ' ' || **s == 'L') && (*s)[-1] == '\n')
			return (0);
		else if (**s == ' ' && *minus < 2)
		{
			*minus = 0;
			(*space)++;
		}
		else if (**s == '-')
			if (*space == 0)
				return (1);
			else
				(*minus)++;
		else if ((*space > 0 && ft_isdigit(**s) == 0)
			|| ft_isprint(**s) == 0 || *minus > 1)
			return (0);
		(*s)++;
	}
	return (2);
}

char		check_room(char **s, t_li *li)
{
	char	space;
	char	minus;
	char	r;

	while (**s != 0)
	{
		(*s)++;
		space = 0;
		minus = 0;
		if (cmd_cmt(s, li) == 0)
			return (0);
		if ((r = real_check(s, &space, &minus)) < 2)
			return (r);
		if (space != 2 || ++(li->nroom) > INT_MAX)
			return (0);
	}
	return (1);
}

static void	set_end_begin(int j, t_li *li)
{
	while (--j >= 0)
	{
		if (ft_strnequ(ROOM[j]->name, li->beg, ft_strlen(ROOM[j]->name)))
			ft_swap((void*)&ROOM[j], (void*)&ROOM[0]);
		if (ft_strnequ(ROOM[j]->name, li->end, ft_strlen(ROOM[j]->name)))
		{
			ft_swap((void*)&ROOM[j], (void*)&ROOM[1]);
			if (ft_strnequ(ROOM[j]->name, li->beg, ft_strlen(ROOM[j]->name)))
				ft_swap((void*)&ROOM[j], (void*)&ROOM[0]);
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
			if (ft_strequ(ROOM[i]->name, ROOM[j]->name) == 1
				|| (ROOM[i]->x == ROOM[j]->x
					&& ROOM[i]->y == ROOM[j]->y))
				return (0);
	}
	return (1);
}

char		save_room(char *s, char *end, t_li *li)
{
	int		j;
	int		len;

	if (!(ROOM = (t_pt**)malloc(sizeof(ROOM) * (li->nroom))))
		return (0);
	j = 0;
	while (s != end)
		if (*s == '#')
			s = s + ft_strclen(s, '\n') + 1;
		else
		{
			len = ft_strclen(s, ' ');
			if (!(ROOM[j] = ft_ptnew(ft_strndup(s, len), 0, 0, 0)))
				return (0);
			s = s + len + 1;
			ROOM[j]->x = ft_atoi(s);
			s = s + ft_strclen(s, ' ') + 1;
			ROOM[j]->y = ft_atoi(s);
			s = s + ft_strclen(s, '\n') + 1;
			j++;
		}
	set_end_begin(j, li);
	if (check_duplicate(li) == 0)
		return (0);
	return (1);
}
