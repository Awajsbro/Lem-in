/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/30 15:27:35 by awajsbro          #+#    #+#             */
/*   Updated: 2018/07/26 15:54:51 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static int	room_number(char *name, char c, t_li *li)
{
	int		i;
	int		len;

	i = 0;
	len = ft_strclen(name, c);
	while (!(ft_strnequ(name, ROOM[i]->name, len))
		|| !(ft_strnequ(name, ROOM[i]->name, ft_strlen(ROOM[i]->name))))
		i++;
	return (i);
}

char		save_pipe(char *s, t_li *li, int i, char *tmp)
{
int debug;

debug = 0;
	while (*(tmp++) != 0)
	{
		cmd_cmt(&tmp, li);
		if (*tmp == '-')
			if ((li->npipe++) > INT_MAX)
				return (0);
	}
	if (!(li->pip = (int**)malloc(sizeof(li->pip) * li->npipe)))
		return (0);
	cmd_cmt(&s, li);
	while (*s != 0 && (li->npipe - i > 0))
	{
		debug++;
		if (!(li->pip[i] = (int*)malloc(sizeof(*(li->pip)) * 2)))
			return (0);
		cmd_cmt(&s, li);
		li->pip[i][0] = room_number(s, '-', li);
		s = s + ft_strclen(s, '-') + 1;
		li->pip[i][1] = room_number(s, '\n', li);
		s = s + ft_strclen(s, '\n') + 1;
		i++;
	}
	cmd_cmt(&s, li);
	return (li->npipe == 0 ? 0 : 1);
}

static char	is_room(char *s, t_li *li)
{
	int		i;
	int		len;
	int		r;

	i = -1;
	len = ft_strclen(s, '-');
	while (++i < li->nroom)
		if (ft_strnequ(s, ROOM[i]->name, len) == 1)
			break ;
	if (i == 0 || i == 1)
		ROOM[i]->z = ROOM[i]->z + 1;
	if (i == li->nroom)
		return (0);
	i = -1;
	s = s + len + 1;
	len = ft_strclen(s, '\n');
	while (++i < li->nroom)
		if ((r = ft_strnequ(s, ROOM[i]->name, len)) == 1)
			break ;
	if (i == 0 || i == 1)
		ROOM[i]->z = (ROOM[i]->z) + 1;
	return (r);
}

static char	is_same_room_pipe(char *s, char *bp, t_li *li)
{
	int		i;
	char	*r2;

	i = ft_strclen(s, '-') + 1;
	if (ft_strnequ(s, &s[i], i - 1))
		if (ft_strnequ(s, &s[i], ft_strclen(&s[i], '\n')))
			return (1);
	r2 = s + ft_strclen(s, '-') + 1;
	cmd_cmt(&bp, li);
	while (bp != s)
	{
		i = ft_strclen(bp, '-');
		if ((ft_strnequ(bp, s, i) && ft_strnequ(bp, s, ft_strclen(s, '-'))
			&& ft_strnequ(&bp[i + 1], r2, ft_strclen(&bp[i + 1], '\n'))
			&& ft_strnequ(&bp[i + 1], r2, ft_strclen(r2, '\n')))
				|| (ft_strnequ(bp, r2, i)
				&& ft_strnequ(bp, r2, ft_strclen(r2, '\n'))
				&& ft_strnequ(&bp[i + 1], s, ft_strclen(&bp[i + 1], '\n'))
				&& ft_strnequ(&bp[i + 1], s, ft_strclen(s, '-'))))
			return (1);
		bp = bp + ft_strclen(bp, '\n') + 1;
		cmd_cmt(&bp, li);
	}
	return (0);
}

char		check_pipe(char **s, t_li *li)
{
	int		j;
	char	minus;
	char	*bp;

	bp = *s + 1;
	while ((++*s)[0] != 0)
	{
		if (cmd_cmt(s, li) == 0)
			return (0);
		j = -1;
		minus = 0;
		while ((*s)[++j] != '\n' && (*s)[j] != 0)
		{
			if ((*s)[j] == '-')
				minus++;
			else if ((*s)[j] == ' ')
				return (0);
		}
		if (minus != 1 || is_room(*s, li) == 0 || is_same_room_pipe(*s, bp, li))
			return (0);
		*s = *s + j;
	}
	ROOM[0]->z = ROOM[0]->z > ROOM[1]->z ? ROOM[1]->z : ROOM[0]->z;
	return (1);
}
