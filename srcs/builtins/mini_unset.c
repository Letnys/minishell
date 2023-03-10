/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 21:00:16 by vkuzmin           #+#    #+#             */
/*   Updated: 2023/03/10 21:21:58 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mini_unset(char **str, t_env **env, t_data *data)
{
	t_env	*current;
	t_env	*prev;

	if (str[2])
		error(ERR_ARGS, str[0], str[1], data);
	prev = NULL;
	current = *env;
	while (current != NULL)
	{
		if (!ft_strncmp(current->full_string, str[1], ft_strlen(current->pref)))
		{
			if (prev != NULL)
				prev->next = current -> next;
			else
				*env = current -> next;
			free(current);
			return ;
		}
		prev = current;
		current = current -> next;
	}
	return ;
}
