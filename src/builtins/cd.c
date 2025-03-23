/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cda-fons <cda-fons@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:13 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/23 17:24:03 by cda-fons         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_oldpwd(t_mini *mini)
{
	char	*oldpwd;
	int	indexoldpwd;

	indexoldpwd = get_index_env(mini, "OLDPWD");
	if (indexoldpwd != -1)
	{
		oldpwd = mini->env[get_index_env(mini, "PWD")] + (ft_strlen("PWD") + 1);
		if (oldpwd)
		{
			free(mini->env[indexoldpwd]);
			mini->env[indexoldpwd] = malloc(ft_strlen("OLDPWD=") + ft_strlen(oldpwd) + 1);
			if (!mini->env[indexoldpwd])
				mini_errors(mini, "Malloc Error: update oldpwd", 1);
			ft_strncpy(mini->env[indexoldpwd], "OLDPWD=", ft_strlen("OLDPWD="));
			ft_strlcat(mini->env[indexoldpwd], oldpwd, ft_strlen(oldpwd));
		}
	}
}

void	update_pwd(t_mini *mini)
{
	char	*pwd;
	int	indexpwd;

	indexpwd = get_index_env(mini, "PWD");
	if (indexpwd != -1)
	{
		pwd = getenv("PWD");
		printf("aqui ta o PWD que o getenv me trouxe -> %s", pwd);
		free(mini->env[indexpwd]);
		mini->env[indexpwd] = malloc(ft_strlen("PWD=") + ft_strlen(pwd) + 1);
		if (!mini->env[indexpwd])
			mini_errors(mini, "Malloc Error: update pwd", 1);
		ft_strncpy(mini->env[indexpwd], "PWD=", ft_strlen("PWD="));
		ft_strlcat(mini->env[indexpwd], pwd, ft_strlen(pwd));
	}
}

int	change_dir(t_mini *mini, char *target)
{
	if (!target)
		mini_errors(mini, "Minishell: cd: HOME not set", 1);
	if (chdir(target) != 0)
		printf("Minishell: cd: %s: No such file or directory\n", target);
	else
	{
		update_oldpwd(mini);
		update_pwd(mini);
	}
	return (0);
}

char	*get_target(char *input, t_mini *mini)
{
	if (!input)
		return (getenv("HOME"));
	if (ft_strncmp(input, "-", ft_strlen(input)) == 0)
		return (mini->env[get_index_env(mini, "OLDPWD")]);
	return (input);
}

int	cd(t_mini *mini, char **input)
{
	char	*target;
	
 	if (input[2])
		printf("Minishell: cd: too many arguments\n");
	else
	{
		target = get_target(input[1], mini);
		if (!target)
			mini_errors(mini, "sem target no cd", 1);
		if (input[1] && ft_strncmp(input[1], "-", 2) == 0)
			printf("%s\n", target);
		change_dir(mini, target);
	}
	return (0);
}
