/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:10:32 by nkhoudro          #+#    #+#             */
/*   Updated: 2023/09/15 03:17:31 by nkhoudro         ###   ########.fr       */
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

void	export(t_exec *exec)
{
	t_export *head;

	head = exec->exp;
	if (!exec)
	{
		g_var.status = 127;
		return ;
	}
	if (exec->exp)
		sort_list(&exec->exp);
	if (exec->cmd->nbr_arg == 0)
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
	if (exec->nbr_cmd > 1)
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
					printf("export: usage: export [-nf] [na");
					printf("me[=value] ...] or export -p \n");
					return (0);
				}
				else if (cmd[i] == ')' || cmd[i] == '(')
				{
					printf("bash: syntax error near ");
					printf("unexpected token `%c'\n", (cmd[i]));
					return (0);
				}
				else
				{
					printf("bash: export: `%s':", (cmd));
					printf(" not a valid identifier\n");
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
		if (!(ft_isalpha(cmd[0]) || cmd[0] == '_') && (!(ft_isalpha(cmd[i - 1]) && cmd[i] == '+' && cmd[i + 1])))
		{
			printf ("bash: export: '%s': not a valid identifier\n", cmd);
			g_var.status = 127;
			return (0);
		}
		if (cmd[i] == '+' && cmd[i + 1] == '=')
			return (2);
		i++;
	}
	return (1);
}

char	**list_clean(char *cmd, int num)
{
	char	**str;
	char	**src;

	str = ft_split(cmd, '='); 
	if (!(*str))
		return (NULL);
	if (num == 2)
	{
		src = ft_split(str[0], '+');
		str[0] = src[0];
	}
	return (str);
}