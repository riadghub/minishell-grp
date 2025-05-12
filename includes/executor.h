/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeer-aa <reeer-aa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:39:05 by gekido            #+#    #+#             */
/*   Updated: 2025/05/12 12:25:06 by reeer-aa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"
# include "parser.h"
# include <limits.h>

typedef struct s_env
{
	char			**vars;
	unsigned char	exit_code;
}					t_env;

int					ft_tablen(char **str);
void				ft_print_params(int argc, char *argv[]);
void				sig_handler(int sig);

t_env				*init_env(char **envp);
void				free_env(t_env *env);
char				*get_env_value(char *var, t_env *env);
void				update_env_var(t_env *env, char *key, char *value);
void				add_env_var(t_env *env, char *var);
void				allocate_new_env(t_env *env, char *var);
int					find_env_var_index(char **vars, char *var, int len);

int					setup_redirections(t_redir *redirects);
int					setup_redirection_in(t_redir *redir);
int					setup_redirection_out(t_redir *redir);
int					setup_redirection_append(t_redir *redir);
int					handle_heredoc(t_redir *redir);

int					execute_command(t_ast_node *node, t_env *env);
int					execute_command_node(t_ast_node *node, t_env *env);
int					execute_builtin(char **args, t_env *env);
int					execute_ast(t_ast_node *node, t_env *env);

int					execute_pipe(t_ast_node *node, t_env *env);
void				execute_pipe_child(t_ast_node *node, t_env *env,
						int *pipefd);
int					execute_pipe_parent(t_ast_node *node, t_env *env,
						int *pipefd, pid_t pid);

int					echo_builtin(char **args);
int					cd_builtin(char **args, t_env *env);
int					pwd_builtin(void);
int					export_builtin(char **args, t_env *env);
int					unset_builtin(char **args, t_env *env);
int					env_builtin(t_env *env);
int					exit_builtin(char **args);

void				execute_external(t_ast_node *node, t_env *env);
void				child_process(t_ast_node *node, t_env *env);
void				parent_process(pid_t pid, t_env *env);
char				*find_path(char *cmd, char **envp);
char				**get_paths(char **envp);
char				*try_path(char *cmd, char *dir);
char				*search_in_paths(char *cmd, char **paths);
char				**convert_env_to_array(t_env *env);
void				free_array(char **arr);

char				*expand_variables(char *str, t_env *env);
void				expand_token_variables(t_token *tokens, t_env *env);

int					is_builtin(char *cmd);
int					is_numeric(const char *str);
void				free_args(char **args);
int					is_valid_n_option(char *arg);

void				setup_signals(void);
void				sigint_handler(int sig);

#endif