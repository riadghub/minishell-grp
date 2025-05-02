/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:04:08 by gekido            #+#    #+#             */
/*   Updated: 2025/05/02 11:03:02 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "executor.h"
# include "expand.h"
# include "lexer.h"
# include "parser.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

extern int	g_signal_status;

void		sigint_handler_no_print(int sig);
void		printbanner(void);
int			handle_input(char *input, char **envp);
void		restore_std_fds(int saved_stdin, int saved_stdout);
int			should_exit(void);
int			get_exit_code(void);
int			process_input(char *input, t_env *env);
void		handle_command(char *input, t_env *env);
void		close_fd(int fd1, int fd2);
void		clean_all(t_env *env, t_token *tokens, t_ast_node *ast);
int			is_unknown_cmd(t_token *tokens, t_env *env);

#endif