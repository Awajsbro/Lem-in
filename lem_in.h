/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:22:56 by awajsbro          #+#    #+#             */
/*   Updated: 2018/06/01 19:09:19 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"

typedef struct	s_li
{
	long	lem;
	long	nroom;
	long	npipe;
	char	*beg;
	char	*end;
	int		**pip;
	int		**way;
	t_pt	**room;
}				t_li;

char			init_anthill(char *s, t_li *li);
void			is_comment(char **s);
char			is_order(char **s, t_li *li);
char			save_room(char *s, char *end, t_li *li);
char			check_room(char **s, t_li *li);
char 			check_pipe(char **s, t_li *li);
char			save_pipe(char *s, t_li *li);
char			path_finding(t_li *li);
void			delete_anthill(char *s, t_li *li);

#endif
