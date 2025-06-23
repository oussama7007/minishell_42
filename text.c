/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 20:29:47 by oait-si-          #+#    #+#             */
/*   Updated: 2025/06/22 23:06:48 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */






static char	*expand_variable(char **end, char *acc,
			char **env, int ex_status)
{
	char	*start;

	if (**end == '?')
	{
		(*end)++;
		return (join_and_free(acc, qestion_mark(ex_status)));
	}
	start = *end;
	while (**end && **end != '"' && (ft_isalnum(**end) || **end == '?'))
		(*end)++;
	return (handle_regular_accumulator(start, *end, env, acc));
}

char	*handle_quoted_part(char **start, int *quotes_type,
			char **env, int ex_status)
{
	char	quote;
	char	*end;
	char	*acc;
	char	ch[2];

	quote = **start;
	*quotes_type = (quote == '"') + 1;
	(*start)++;
	if (quote == '\'')
		return (single_quotes_handler(start));
	acc = ft_strdup("");
	end = *start;
	while (*end && *end != '"')
	{
		if (*end == '$' && (ft_isalpha(*(end + 1)) || *(end + 1) == '?'))
		{
			end++;
			acc = expand_variable(&end, acc, env, ex_status);
		}
		else
		{
			ch[0] = *end;
			ch[1] = '\0';
			acc = join_and_free(acc, ft_strdup(ch));
			end++;
		}
	}
	if (*end != '"')
		return (free(acc), NULL);
	*start = end + 1;
	return (acc);
}

void sigint_handler(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    rl_on_new_line();           // Prepare for new line
    rl_replace_line("", 0);     // Clear current line buffer
    rl_redisplay();             // Redisplay prompt
}

void setup_signal_handlers(void)
{
    signal(SIGINT, sigint_handler); // Handle Ctrl+C
    signal(SIGQUIT, SIG_IGN);       // Ignore Ctrl+\
}
