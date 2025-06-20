static char	*handle_regular_accumulator(char *var_name, char *end, \
		char *var_start, char **env, char **accumulator);

static char	*handle_question_mark(char **end_ptr, int ex_status, \
		char *accumulator)
{
	char	*end;
	char	*tmp;

	end = *end_ptr;
	tmp = accumulator;
	accumulator = ft_strjoin(tmp, qestion_mark(ex_status));
	free(tmp);
	end++;
	*end_ptr = end;
	return (accumulator);
}

static char	*handle_double_quote_dollar(char **end_ptr, \
		char **env, char *accumulator)
{
	char	*end;
	char	*quote_start;

	end = *end_ptr;
	end++;
	quote_start = end;
	while (*end && *end != '"')
		end++;
	if (*end == '"')
		accumulator = accumulator_unquote_part(env, &end, quote_start, \
				&accumulator);
	else
	{
		free(accumulator);
		return (NULL);
	}
	*end_ptr = end;
	return (accumulator);
}

static char	*handle_regular_dollar(char **end_ptr, \
		char **env, char *accumulator)
{
	char	*end;
	char	*var_start;

	end = *end_ptr;
	var_start = end;
	while (*end && (ft_isalnum(*end) || *end == '_' || *end == '?') && \
			*end != ' ' && *end != '\t' && *end != '|' && \
			*end != '<' && *end != '>' && *end != '\'' && *end != '"')
		end++;
	accumulator = handle_regular_accumulator(NULL, end, var_start, env, \
			&accumulator);
	*end_ptr = end;
	return (accumulator);
}

static char	*handle_dollar_case(char **end_ptr, \
		char **env, int ex_status, char *accumulator)
{
	char	*end;

	end = *end_ptr;
	end++;
	if (*end == '?')
		accumulator = handle_question_mark(&end, ex_status, accumulator);
	else if (*end == '"')
		accumulator = handle_double_quote_dollar(&end, env, accumulator);
	else
		accumulator = handle_regular_dollar(&end, env, accumulator);
	*end_ptr = end;
	return (accumulator);
}

static char	*handle_normal_char(char **end_ptr, char *accumulator)
{
	char	*end;
	char	*tmp;
	char	chr_str[2];

	end = *end_ptr;
	chr_str[0] = *end;
	chr_str[1] = '\0';
	tmp = accumulator;
	accumulator = ft_strjoin(tmp, chr_str);
	free(tmp);
	end++;
	*end_ptr = end;
	return (accumulator);
}

static char	*handle_unquoted_part(char **start, int *quotes_type, \
		char **env, int ex_status)
{
	char	*accumulator;
	char	*end;

	accumulator = NULL;
	end = *start;
	*quotes_type = 0;
	while (*end && *end != ' ' && *end != '\t' && *end != '|' && \
			*end != '<' && *end != '>' && *end != '\'' && *end != '"')
	{
		if (*end == '$' && (ft_isalpha(*(end + 1)) || \
				*(end + 1) == '_' || *(end + 1) == '?' || *(end + 1) == '"')
			accumulator = handle_dollar_case(&end, env, ex_status, accumulator);
		else
			accumulator = handle_normal_char(&end, accumulator);
	}
	*start = end;
	if (!accumulator)
		accumulator = ft_strdup("");
	return (accumulator);
}

static char	*handle_regular_accumulator(char *var_name, char *end, \
		char *var_start, char **env, char **accumulator)
{
	char	*tmp;
	char	*var_value;
	char	*temp;

	(void)var_name;
	var_name = ft_strndup(var_start, end - var_start);
	var_value = get_var_value(var_name, env);
	temp = *accumulator;
	*accumulator = ft_strjoin(temp, var_value);
	free(temp);
	free(var_name);
	return (*accumulator);
}

static char	*singel_quotes_handler(char **start)
{
	char	*accumulator;
	char	*end;

	end = *start;
	while (*end && *end != '\'')
		end++;
	if (*end != '\'')
		return (NULL);
	accumulator = ft_strndup(*start, end - *start);
	end++;
	*start = end;
	return (accumulator);
}