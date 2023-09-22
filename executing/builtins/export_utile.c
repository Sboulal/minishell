/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:10:32 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/22 12:54:54 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/exec.h"

void	edit_in_string(t_envp *env)
{
	int	i;

	i = 0;
	while (g_var.env[i] && ft_strncmp(g_var.env[i], "SHLVL=", 6) != 0)
		i++;
	if (g_var.env[i])
		g_var.env[i] = ft_strdup(env->env);
}

void	export(t_exec **exec)
{
	t_export *head;

	if (!(*exec))
	{
		g_var.status = 127;
		return ;
	}
	head = (*exec)->exp;
	if ((*exec)->exp)
		sort_list(&(*exec)->exp);
	if ((*exec)->cmd->nbr_arg == 0)
	{
		while (head)
		{
			printf("declare -x %s\n", head->exp);
			head = head->next;
		}
	}
	else
		add_to_export(exec);
	g_var.status = 0;
	if ((*exec)->nbr_cmd > 1)
		exit(0);
}

int	check_error_export(char *cmd, int i)
{
	if (!ft_isalpha(cmd[i]))
	{
		if (cmd[i] != '!' && cmd[i] != '#')
		{
			if (cmd[i] != '$' && cmd[i] != '&' && cmd[i] != '_')
			{
				if (cmd[i] == '-')
				{
					ft_putstr_fd("export: usage: export [-nf] [na", 2);
					ft_putstr_fd("me[=value] ...] or export -p \n", 2);
					return (0);
				}
				else if (cmd[i] == ')' || cmd[i] == '(')
				{
					ft_putstr_fd("minishell: syntax error near ", 2);
					ft_putstr_fd("unexpected token `", 2);
					ft_putchar_fd(cmd[i], 2);
					ft_putstr_fd("'\n", 2);
					return (0);
				}
				else
				{
					ft_putstr_fd("minishell: export: `", 2);
					ft_putstr_fd(cmd, 2);
					ft_putstr_fd("': not a valid identifier\n", 2);
					return (0);
				}
			}
		}
	}
	return (1);
}

int	check_export(char *cmd)
{
	int	i;

	i = 0;
	if (check_error_export(cmd, i) == 0)
		return (0);
	while (cmd[i + 1])
	{
		if (cmd[i] == '+' && cmd[i + 1] == '=')
			return (2);
		else if (cmd[i] == '+')
		{
			printf ("bash: export: '%s': not a valid identifier\n", cmd);
			g_var.status = 127;
			return (0);
		}
		if (!(ft_isalpha(cmd[0]) || cmd[0] == '_') && (!(i != 0 && cmd[i + 1] && ft_isalpha(cmd[i - 1]) && cmd[i] == '+' && cmd[i + 1])))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_var.status = 127;
			return (0);
		}
		i++;
	}
	return (1);
}
int	check_unset(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!(is_identifier(cmd[i])) || ft_isdigit(cmd[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_var.status = 127;
			return (0);
		}
		i++;
	}
	return (1);
}
int	check_unset_env(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (!(is_identifier(cmd[i])) && !ft_isdigit(cmd[i]))
		{
			g_var.status = 127;
			return (0);
		}
		i++;
	}
	return (1);
}
char **my_split_word(char *cmd, char c)
{
	int i;
	char **str;
	char *tmp;

	i = 0;
	tmp = cmd;
	while (tmp[i])
	{
		if (tmp[i] == c)
			break;
		i++;
	}
	if (tmp[i])
	{
		str = (char **)malloc(sizeof(char *) * 3);
		str[0] = ft_substr(tmp, 0, i);
		str[1] = ft_substr(tmp, i + 1, ft_strlen(tmp));
		str[2] = NULL;
		return (str);
	}
	//0x10000B779
	//0x100009482
	//0x100009574
	//0x100008AE7
	//0x100008CA0
	// 0x100002E65
	str = (char **)malloc(sizeof(char *) * 2);
	str[0] = ft_substr(cmd, 0, ft_strlen(cmd));
	str[1] = NULL;
	return (str);
}
char	**list_clean(char *cmd, int num)
{
	char	**str;
	char *tmp;
	char	**src;

	if (!cmd)
		return (NULL);
	tmp = cmd;
	str = my_split_word(tmp, '='); 
	if (!(*str))
		return (NULL);
	if (num == 2)
	{
		tmp = str[0];
		src = my_split_word(tmp, '+');
		str[0] = src[0];
		printf("src[0] = %p\n", src);
	}
	return (str);
}
