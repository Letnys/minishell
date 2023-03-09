/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egeorgel <egeorgel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 19:01:45 by egeorgel          #+#    #+#             */
/*   Updated: 2023/03/09 19:46:10 by egeorgel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	data_initialize(t_data *data, char **envp)
{
	data->prompt = NULL;
	data->in_fd = 0;
	data->out_fd = 1;
	get_errlst(data);
	data->envp = NULL;
	data->env = NULL;
	create_env(envp, &data->env);
	get_path(data);
	update_envp(data);
}

void	data_default(t_data *data)
{
	data->prompt = NULL;
	data->in_fd = 0;
	data->out_fd = 1;
	update_envp(data);
}

void	minishell_loop(t_data *data)
{
	data->prompt = readline("-> ");
	errno = 0;
	data->lst = sep_token(data->prompt, data);
	if (!data->lst)
		return ;
	while (callstructure(data))
	{
	}
	close(data->in_fd);
	waitpid(data->pid, NULL, 0);
	free(data->prompt);
	data_default(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	argc = 0;
	argv[0][0] = '0';
	data_initialize(&data, envp);
	while (1)
		minishell_loop(&data);
}
//errno = 0 because readline sets errno to 2 for some reason