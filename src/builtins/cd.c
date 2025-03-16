/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alberto <alberto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 15:24:13 by cda-fons          #+#    #+#             */
/*   Updated: 2025/03/08 23:52:44 by alberto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_error(char *str)
{
	printf("%s\n", str);
	return (1);
}

void update_env(char *cwd)
{
	char *oldpwd = getenv("PWD");
	if (oldpwd)
		setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", cwd, 1);
	printf("updated_env OLDPWD com getenv final: %s\n", getenv("OLDPWD"));
	printf("updated_env PWD com getenv final: %s\n", getenv("PWD"));
}

int	change_dir(char *target)
{
	char cwd[PATH_MAX];

	printf("change_dir target: %s\n", &target[1]);
	if (!target)
		return (ft_error("cd: HOME not set\n"));
	if (chdir(target) != 0)
		return (ft_error("cd"));
	if (!getcwd(cwd, sizeof(cwd)))
		return (ft_error("getcwd"));
	update_env(cwd);
	return (0);
}

char *get_target(char **args)
{
	if (!args[1])
	{
		printf("return home: %s\n", getenv("HOME"));
		return (getenv("HOME"));
	}
	if (ft_strncmp(args[1], "-", ft_strlen(args[1])) == 0)
		return (getenv("OLDPWD"));
	return (args[1]);
}

void	cd(t_mini *mini)
{
	char *target;

	target = get_target(mini->args);
	if (!target)
		return ;
	printf("return do get_target no cd: %s\n", target);
	if (mini->args[1] && ft_strncmp(mini->args[1], "-", 2) == 0)
		printf("%s\n", target);
	change_dir(target);
}

int main(int argc, char *argv[])
{
	t_mini	*mini = (t_mini *)malloc(sizeof(t_mini));

	(void)argc;
	mini->args = argv;
    cd(mini);
    return 0;
}