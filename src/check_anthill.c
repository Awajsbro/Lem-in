/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_anthill.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:01:22 by awajsbro          #+#    #+#             */
/*   Updated: 2018/05/30 18:20:00 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lem_in.h"

static void	delete_line(char **s)
{
	if (**s == '\n')
		(*s)--;
	while (**s != '\n')
		(*s)--;
	**s = 0;
}

void		is_comment(char **s)
{
	while (**s != 0 && **s == '#' && (*s)[1] != '#')
		while ((*s)[-1] != '\n' && **s != 0)
			(*s)++;
}

char		is_order(char **s, t_li *li)
{
	char	**tmp;

	tmp = NULL;
	if (ft_strnequ(*s, "##end\n", 6) == 1)
	{
		*s += 6;
		if (li->beg != NULL)
			return (0);
		tmp = &li->beg;
	}
	else if (ft_strnequ(*s, "##start\n", 8) == 1)
	{
		*s +=8;
		if (li->end != NULL)
			return (0);
		tmp = &li->end;
	}
	if (tmp != NULL)
	{
		is_comment(s);
		if (is_order(s, li) == 0)
			return (0);
		*tmp = *s;
	}
	return (1);
}

char		init_anthill(char *s, t_li *li)
{
	char	tmp[21];
	char	*tmp2;

	li->nroom = 0;
	li->npipe = 0;
	is_comment(&s);
	li->lem = ft_atoi(s);
	if (ft_istrcmp("2147483648", ft_strncpy(tmp, s, ft_strclen(s, '\n'))) == -1
		|| li->lem < 1)
		return (0);
	while (*s != '\n' && *s != 0)
		s++;
	tmp2 = s + 1;
	if (check_room(&s, li) == 0 || li->end == NULL || li->beg == NULL)
		return (0);
	if (*s == '-')
		while (s[-1] != '\n')
			s--;
	if (!(save_room(tmp2, s, li)) || (li->end != NULL || li->beg != NULL))
		return (0);
	tmp2 = s;
	if (check_pipe(&s, li) == 0)
		delete_line(&s);
	if (!(save_pipe(tmp2, li)))
		return (0);
	return (1);
}
