/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:10:32 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/28 20:58:31 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	edit_in_string(t_exec **exp, t_envp *env)
{
	int	i;

	i = 0;
	while ((*exp)->env_string[i] && ft_strncmp((*exp)->env_string[i], "SHLVL=", 6) != 0)
		i++;
	if ((*exp)->env_string[i])
		(*exp)->env_string[i] = ft_strdup(env->env);
}

void	export(t_exec **exec)
{
	t_export *head;


	if (!(*exec))
	{
		g_var.status = 1;
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
		g_var.status = 0;
	}
	else
		add_to_export(exec);
	if ((*exec)->nbr_cmd > 1)
		exit(g_var.status);
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
					g_var.status = 1;
					return (0);
				}
				else if (cmd[i] == ')' || cmd[i] == '(')
				{
					ft_putstr_fd("minishell: syntax error near ", 2);
					ft_putstr_fd("unexpected token `", 2);
					ft_putchar_fd(cmd[i], 2);
					ft_putstr_fd("'\n", 2);
					g_var.status = 1;
					return (0);
				}
				else
				{
					ft_putstr_fd("minishell: export: `", 2);
					ft_putstr_fd(cmd, 2);
					ft_putstr_fd("': not a valid identifier\n", 2);
					g_var.status = 1;
					return (0);
				}
			}
		}
	}
	return (1);
}
int	check_before_equal(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && cmd[i] != '=')
	{
		if (!is_identifier(cmd[i]) && cmd[i] != '+')
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_var.status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}
int	check_export(char *cmd)
{
	int	i;

	i = 0;
	if (check_error_export(cmd, i) == 0)
		return (0);
	while (cmd[i] && cmd[i] != '=')
	{
		if (cmd[i + 1]  && cmd[i] == '+' && cmd[i + 1] == '=')
			return (2);

		else if (cmd[i] == '+')
		{
			printf ("bash: export: '%s': not a valid identifier\n", cmd);
			g_var.status = 1;
			return (0);
		}
		if (!(ft_isalpha(cmd[0]) || cmd[0] == '_') && (!(i != 0 && cmd[i + 1] && ft_isalpha(cmd[i - 1]) && cmd[i] == '+' && cmd[i + 1])))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_var.status = 1;
			return (0);
		}
		i++;
	}
	if (!check_before_equal(cmd))
		return (0);
	return (1);
}
int	check_unset(char *cmd)
{int	i;

	i = 1;
	if (!(ft_isalpha(cmd[0]) || cmd[0] == '_'))
	{
		g_var.status = 1;
		return (0);
	}
	while (cmd[i])
	{
		if (!(ft_isalpha(cmd[0]) || cmd[0] == '_'))
		{
			g_var.status = 1;
			return (0);
		}
		i++;
	}
	return (1);
}
int	check_unset_env(char *cmd)
{
	int	i;

	i = 1;
	if (!(ft_isalpha(cmd[0]) || cmd[0] == '_'))
	{
		g_var.status = 1;
		return (0);
	}
	while (cmd[i])
	{
		if (!(ft_isalpha(cmd[0]) || cmd[0] == '_'))
		{
			g_var.status = 1;
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
	// char *tmp1;
	// char *tmp2;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == c)
			break;
		i++;
	}
	if (cmd[i])
	{
		str = (char **)malloc(sizeof(char *) * 3);
		tmp = cmd;
		str[0] = ft_substr(tmp, 0, i);
		str[1] = ft_substr(tmp, i + 1, ft_strlen(tmp));
		// fre/e(tmp);
		str[2] = NULL;
		return (str);
	}
	str = (char **)malloc(sizeof(char *) * 2);
	str[0] = ft_substr(cmd, 0, ft_strlen(cmd));
	str[1] = NULL;
	return (str);
}
char	**list_clean(char *cmd, int num)
{
	char	**str;
	char	**src;
	char *tmp1;
	int 	i;

	i = 0;
	str = my_split_word(cmd, '='); 
	if (!(*str))
		return (NULL);
	if (num == 2)
	{
		tmp1 = str[0];
		src = my_split_word(tmp1, '+');
		str[0] = ft_strdup(src[0]);
		while(src[i])
			free(src[i++]);
		free(tmp1);
	}
	return (str);
}
