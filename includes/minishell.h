/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:04:08 by gekido            #+#    #+#             */
/*   Updated: 2025/04/21 22:38:59 by gekido           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>

# include "../libft/libft.h"
# include "lexer.h"
# include "parser.h"
# include "executor.h"
# include "expand.h"

extern int	g_signal_status;

void	printbanner(void);
int		handle_input(char *input, char **envp);
void	restore_std_fds(int saved_stdin, int saved_stdout);
int		should_exit(void);
int		get_exit_code(void);
int		process_input(char *input, t_env *env);
void	handle_command(char *input, t_env *env);
void	close_fd(int fd1, int fd2);
void	clean_all(t_env *env, t_token *tokens, t_ast_node *ast);
int		is_unknown_cmd(t_token *tokens, t_env *env);

#endif