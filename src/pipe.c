/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:27:35 by awajsbro          #+#    #+#             */
/*   Updated: 2018/06/01 19:18:56 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int	room_number(char *name, char c, t_li *li)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strclen(name, c);
	while (!(ft_strnequ(name, li->room[i]->name, len)))
		i++;
	return (i);
}

char		save_pipe(char *s, t_li *li)
{
	char	*tmp;
	int		i;

	tmp = s;
	while(*(tmp++) != 0)
		if (*tmp == '-')
			if ((li->npipe++) > INT_MAX)
				return (0);
	if (!(li->pip = (int**)malloc(sizeof(li->pip) * li->npipe)))
		return (0);
	i = 0;
	while (*s != 0)
	{
		if (!(li->pip[i] = (int*)malloc(sizeof(*(li->pip)) * 2)))
			return (0);
		is_comment(&s);
		li->pip[i][0] = room_number(s, '-', li);
		s = s + ft_strclen(s, '-') + 1;
		li->pip[i][1] = room_number(s, '\n', li);
		s = s + ft_strclen(s, '\n') + 1;
		i++;
	}
	return (1);
}

static char is_room(char *s, t_li *li)
{
	int		i;
	int		len;

	i = -1;
	len = ft_strclen(s, '-');
	while (++i < li->nroom)
		if (ft_strnequ(s, li->room[i]->name, len) == 1)
			break ;
	if (i == 0 || i == 1)
		li->room[i]->z = (li->room[i]->z)++;
	if (i == li->nroom)
		return (0);
	i = -1;
	s = s + len + 1;
	len = ft_strclen(s, '\n');
	while (++i < li->nroom)
		if (ft_strnequ(s, li->room[i]->name, len) == 1)
			return (1);
	if (i == 0 || i == 1)
		li->room[i]->z = (li->room[i]->z)++;
	return (0);
}

char check_pipe(char **s, t_li *li)
{
	int		j;
	char	minus;

	while ((++*s)[0] != 0)
	{
		is_comment(s);
		j = -1;
		minus = 0;
		while ((*s)[++j] != '\n' && (*s)[j] != 0)
		{
			if ((*s)[j] == '-')
				minus++;
			else if ((*s)[j] == ' ')
				return (0);
		}
		if (minus != 1 || is_room(*s, li) == 0)
			return (0);
		*s = *s + j;
	}
	return (1);
}
