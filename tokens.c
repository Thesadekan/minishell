/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-boul <ael-boul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 16:03:46 by ael-boul          #+#    #+#             */
/*   Updated: 2025/06/15 16:16:20 by ael-boul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_type type_arg(char *str)
{
	if (ft_strcmp(str, ">") == 0)
		return TRUNC;
	else if (ft_strcmp(str, ">>") == 0)
		return APPEND;
	else if (ft_strcmp(str, "<") == 0)
		return INPUT;
	else
		return CMD; // Non-redirection tokens are CMD (or ARG, decided later)
}

char *next_token(char *line, int *i)
{
	char *token;
	int j = 0;
	// int start = *i;
	char c = ' ';

	// First, compute how much space we need
	int len = 0;
	int k = *i;
	while (line[k] && (line[k] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[k] == '\'' || line[k] == '\"'))
			c = line[k++];
		else if (c != ' ' && line[k] == c)
		{
			c = ' ';
			k++;
		}
		else if (line[k] == '\\' && line[k + 1])
			k += 2;
		else
			k++;
		len++;
	}

	// Allocate the token string
	token = malloc(sizeof(char) * (len + 1));
	if (!token)
		return (NULL);

	c = ' ';
	while (line[*i] && (line[*i] != ' ' || c != ' '))
	{
		if (c == ' ' && (line[*i] == '\'' || line[*i] == '\"'))
			c = line[(*i)++];
		else if (c != ' ' && line[*i] == c)
		{
			c = ' ';
			(*i)++;
		}
		else if (line[*i] == '\\' && line[*i + 1])
		{
			(*i)++;
			token[j++] = line[(*i)++];
		}
		else
			token[j++] = line[(*i)++];
	}
	token[j] = '\0';
	return token;
}

t_cmd *get_tokens(char *line)
{
	t_cmd *cmd_head = NULL;
	t_cmd *current = NULL;

	int i = 0;
	ft_skip_space(line, &i);

	while (line[i])
	{
		t_cmd *new_cmd = ft_calloc(1, sizeof(t_cmd));
		t_redirections *redir_tail = NULL;
		int arg_count = 0;

		while (line[i] && line[i] != '|')
		{
			char *token = next_token(line, &i); // You must implement this similar to next_token()
			if (!token)
				break;

			t_cmd_type type = type_arg(token); // You must implement this, like type_arg() before
			if (type == CMD || type == ARG)
			{
				new_cmd->args = realloc(new_cmd->args, sizeof(char *) * (arg_count + 2));
				new_cmd->args[arg_count++] = token;
				new_cmd->args[arg_count] = NULL;
			}
			else if (type == TRUNC || type == APPEND || type == INPUT)
			{
				t_redirections *redir = ft_calloc(1, sizeof(t_redirections));
				redir->type = type;

				ft_skip_space(line, &i);
				char *filename = next_token(line, &i); // Must follow redirection token
				redir->value = filename;
				redir->next = NULL;

				if (!new_cmd->redirections)
					new_cmd->redirections = redir;
				else
					redir_tail->next = redir;
				redir_tail = redir;
			}

			ft_skip_space(line, &i);
		}

		if (new_cmd->args)
			new_cmd->cmd = ft_strdup(new_cmd->args[0]);

		if (!cmd_head)
			cmd_head = new_cmd;
		else
			current->next = new_cmd;

		current = new_cmd;

		if (line[i] == '|')
			i++; // skip pipe

		ft_skip_space(line, &i);
	}

	return cmd_head;
}
