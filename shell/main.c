/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 09:07:19 by iomayr            #+#    #+#             */
/*   Updated: 2022/09/02 12:37:54 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void ft_sig_handler(int sig)
{
	if (sig == 3)
	{
		if (g_global.catch_signal ==  1 && ft_strncmp(g_global.tmp_readline, "./minishell", 11))
			printf("Quit : 3\n");
		else if (g_global.catch_signal == 0)
			rl_replace_line("", 0);
	}	
	if (sig == 2)
	{
		if (g_global.catch_signal == 0)
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (g_global.catch_signal == 1 && ft_strncmp(g_global.tmp_readline, "./minishell", 11))
			printf("\n");
	}
}

void handle_signal(void)
{
	signal(SIGQUIT, ft_sig_handler);
	signal(SIGINT, ft_sig_handler);
}

t_free	*ft_lstnew1(void *content)
{
	t_free	*node;

	node = (t_free *)malloc(sizeof(t_free));
	if (!node)
		return (NULL);
	node->to_free = content;
	node->next = NULL;
	return (node);
}

t_free	*ft_lstlast1(t_free *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back1(t_free **collecter, t_free *new)
{
	if (!collecter || !new)
		return ; // error
	new->next = *collecter;
	*collecter = new;
}


void	*ft_malloc(size_t size)
{
	void *head;

	head = malloc(size);
	ft_lstadd_back1(&g_global.free_collect, ft_lstnew1(head));
	return (head);
}

void	collect_libft_readline(void *to_collect)
{
	ft_lstadd_back1(&g_global.free_collect, ft_lstnew1(to_collect));
}


void	free_list(t_free* list) {
    if (!list)
        return ;
    free_list(list->next);
    free(list->to_free);
	free(list);
}


// void	free_list(t_free *list)
// {
// 	while(list)
// 	{
// 		printf("laaa\n");
// 		free(list->to_free);
// 		printf("%p\n", list->to_free);
// 		list = list->next;
// 	}
// }


int main(int ac, char **av, char **env)
{
	t_main v_main;
	int     IO[2];

	IO[0] = dup(0);
	IO[1] = dup(1);

	ft_initialize_env(&v_main, ac, av, env);
	while (1)
	{
		dup2(IO[0], 0);
		dup2(IO[1], 1);
		handle_signal();
		g_global.catch_signal = 0;
		v_main.line = readline("\e[1;32m➜  \e[1;31mMini👽shell\e[1;33m ➤ \e[1;37m\e[m");
		g_global.tmp_readline = v_main.line;
		collect_libft_readline(v_main.line);
		if (v_main.line == NULL)
			break ;
		add_history(v_main.line);
		v_main.list = ft_lexer(v_main.line, &v_main);
		if(v_main.list == NULL)
			return (0);
		if (!check_syntax(v_main.list, &v_main))
		{
			printf("cmd = %p \n cmcd->cmd = %p \n  \n", v_main.cmd, v_main.cmd->command);
			v_main.cmd = ft_parse(v_main.list, v_main.h_env);
			printf("cmd = %p \n cmcd->cmd = %p \n  \n", v_main.cmd, v_main.cmd->command);
			if (list_cmd_size(v_main.cmd) == 1)
				simple_command(&v_main);
			else if (list_cmd_size(v_main.cmd) > 1) 
				run_multi_cmd(&v_main);
			// printf("%s\n", v_main.cmd->command[0]);
		}
		g_global.quotes_count = 0;
		// free(v_main.line);
	}
	free_list(g_global.free_collect);
	close(IO[0]);
	close(IO[1]);
	return (0);
}