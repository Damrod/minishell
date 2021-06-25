/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nazurmen <nazurmen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 18:44:16 by hellnhell         #+#    #+#             */
/*   Updated: 2021/06/25 16:08:36 by nazurmen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <minishell0.h>
# include	<libft.h>
# include	<stdio.h>
# include	<unistd.h>
# include	<string.h>
# include	<stdlib.h>
# include	<errno.h>

typedef struct s_tab
{
	char		*line;
	char		**tokens;
	char		**our_env;
	char		**path;
	char		**path_token;
	char		**orders;
}					t_tab;

char	*read_line(t_tab *t);
//void	read_path(t_tab *t, char **env);
void	read_path(char **env, t_term	*g_term);
//void	check_path(t_tab *t, char **env);
void	check_path(t_term *g_term);
char	**split_line(char *line);
void	*ft_realloc(void *ptr, size_t originalsize, size_t newsize);
char	*ft_strtok(char *str, char *sepa);
char	*ft_strjoin_sl(const char *s1, const char *s2);
int		ft_echo(char **args);
int		ft_pwd(void);
int		ft_cd(char **args);
char	**ft_split_com(char const *s, char c, t_tab *t);
int		check_our_implement(t_tab *t);

#endif
