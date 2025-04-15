/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gekido <gekido@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:04:08 by gekido            #+#    #+#             */
/*   Updated: 2025/04/12 19:53:43 by gekido           ###   ########.fr       */
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

#endif