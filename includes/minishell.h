/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:59 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/18 01:02:25 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h> 
# include <stdio.h> 
# include <unistd.h> 
# include <sys/wait.h> 
# include <sys/types.h> 
# include <fcntl.h> 
# include <termio.h> 
# include <signal.h> 
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/resource.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stdlib.h>
# include <stdbool.h>
# include "../Libft/libft.h"
# include <sys/stat.h>

# define NAME_SHELL "Minishell: "


typedef	struct	s_mini
{
	char	**env;
}				t_mini;


//errors_utils.c
void	error_message(char *message);
void	mini_errors(t_mini *mini, char *message, int errnbr);

//			builtins
//cd
int	cd(t_mini *mini, char **input);
char	*get_target(char *input, t_mini *mini);
int	change_dir(t_mini *mini, char *target);
void	update_env(t_mini *mini);

//env
int	env(char **args);

//pwd
int	pwd(void);

//echo
int	echo(char *str);

//utils.c
int get_index_env(t_mini *mini, char *var);

#endif