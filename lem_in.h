/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awajsbro <awajsbro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 12:22:56 by awajsbro          #+#    #+#             */
/*   Updated: 2018/07/16 16:01:17 by awajsbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"

# define ROOM (li->room)

typedef struct	s_li
{
	long	lem;
	long	nroom;
	long	npipe;
	char	*beg;
	char	*end;
	char 	*str;
	t_list	*lsp;
	int		**pip;
	int		**way;
	t_pt	**room;
}				t_li;

char			init_anthill(char *s, t_li *li);
char			cmd_cmt(char **s, t_li *li);
char			save_room(char *s, char *end, t_li *li);
char			check_room(char **s, t_li *li);
char 			check_pipe(char **s, t_li *li);
char			save_pipe(char *s, t_li *li, int i, char *tmp);
char			path_finding(t_li *li);
void			choose_path(int sim, t_li *li);
void			delete_anthill(char *s, t_li *li);

#endif
// inondation eau commence a 0 et monte de 1 par tour donne le nombre de fourmis sauver a la fin

// garde manger une fourmis au moins doit aller chercher le repas pour le reste

// visualiser
