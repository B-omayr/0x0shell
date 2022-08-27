/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 09:07:19 by iomayr            #+#    #+#             */
/*   Updated: 2022/08/27 18:22:13 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
	t_main v_main;
	t_lexer *lexer;
	int     IO[2];

	IO[0] = dup(0);
	IO[1] = dup(1);
	lexer = NULL;
	ft_initialize_env(&v_main, ac, av, env);
	while (1)
	{
		dup2(IO[0], 0);
		dup2(IO[1], 1);
		v_main.line = readline("\e[1;32m➜  \e[1;31mMini👽shell\e[1;33m ➤ \e[1;37m\e[m");
		if (v_main.line == NULL)
			return (0);
		add_history(v_main.line);
		v_main.list = ft_lexer(v_main.line, &v_main);
		if(v_main.list == NULL)
			return (0); 
		if (!check_syntax(v_main.list, v_main))
		{
			v_main.cmd = ft_parse(v_main.list, v_main.h_env); /*You will work with this pointer*/
			if (list_cmd_size(v_main.cmd) == 1)
				simple_command(&v_main);
			else if (list_cmd_size(v_main.cmd) > 1) 
				run_multi_cmd(&v_main);
			close(0);
			// waitpid(-1, 0, 0);
				// handel_redirections(v_main.cmd);
			// if (is_it_builtin(v_main.cmd->command))
			// 	excute_builtins(v_main.cmd->command, &v_main.h_env);
	   }
		// t_tokens_list *temp;
		// temp = v_main.list;
		// while (temp != NULL)
		// {
		//     printf("type : {%d}; Value : {%s}\n", temp->type, temp->value);
		//     temp = temp->next;
		// } 
		
	   
		// t_command *temp;
		// temp = v_main.cmd;
		// int i = 0;
		// int j = 0;
		
		// while (temp != NULL)
		// {
		//     i = 0;
		//     while (temp->command[i] != NULL)
		//     {
		//         printf("%d : arg : %s, %d\n",j, temp->command[i], temp->separator);
		//         i++;
		//     }
		//     j++;
		//     temp = temp->next;
		// }
		// free(v_main.line);
	}
	close(IO[0]);
	close(IO[1]);
	return (0);
}