/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youchenn <youchenn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/04 08:38:12 by youchenn          #+#    #+#             */
/*   Updated: 2022/09/04 09:04:40 by youchenn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_sig_handler(int sig)
{
	if (sig == 3)
	{
		if (g_global.catch_signal == 1 && \
			ft_strncmp(g_global.tmp_readline, "./minishell", 11))
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
		else if (g_global.catch_signal == 1 && \
			ft_strncmp(g_global.tmp_readline, "./minishell", 11))
			printf("\n");
		g_global.exist_status = 128 + sig;
	}
}

void	handle_signal(void)
{
	signal(SIGQUIT, ft_sig_handler);
	signal(SIGINT, ft_sig_handler);
}
