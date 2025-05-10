// --- HELPER FUNCTION: Validate Shell Variable Name ---
// POSIX: Starts with letter or underscore, followed by letters, digits, or underscores.
static int is_valid_identifier(const char *name)
{
	if (!name || (!isalpha(*name) && *name != '_'))
		return (0); // Must start with a letter or underscore
	name++;
	while (*name)
	{
		if (!isalnum(*name) && *name != '_')
			return (0); // Subsequent chars must be alphanumeric or underscore
		name++;
	}
	return (1);
}

// --- HELPER FUNCTION: Print for 'export' (no args) ---
// This would ideally sort. For simplicity here, it just prints.
// Sorting requires duplicating envp, sorting the copy, printing, then freeing copy.
static void print_export_env(char **envp)
{
	int i = 0;
	char *eq_ptr;
	char *name;
	char *value;

	// TODO: For full compliance, duplicate envp, sort it, then iterate the sorted copy.
	// char **sorted_envp = duplicate_and_sort_envp(envp);
	// if (!sorted_envp) { /* handle error */ return; }
	// char **iter_envp = sorted_envp;

	char **iter_envp = envp; // Using original for now (unsorted)

	while (iter_envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		eq_ptr = ft_strchr(iter_envp[i], '=');
		if (eq_ptr)
		{
			// Temporarily null-terminate name for printing (or strndup)
			*eq_ptr = '\0';
			name = iter_envp[i];
			value = eq_ptr + 1;
			ft_putstr_fd(name, STDOUT_FILENO);
			*eq_ptr = '='; // Restore the '='
			
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		else // Variable exists but has no '=' (e.g. from 'export VAR' then 'unset VAR')
		     // Or if it was set as 'VAR' without value initially.
		{
			ft_putstr_fd(iter_envp[i], STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
	// if (sorted_envp) free_string_array(sorted_envp);
}

// --- THE MAIN ft_export FUNCTION ---
int ft_export(char **args, char ***env_ptr)
{
	int i;
	int ret_status = 0; // 0 for success, 1 for error (e.g., invalid identifier)
	char *arg;
	char *name;
	char *value;
	char *eq_ptr;

	if (!env_ptr || !(*env_ptr)) // Should not happen if env is initialized
		return (1);

	if (!args[1]) // Case 1: `export` called with no arguments
	{
		print_export_env(*env_ptr);
		return (0);
	}

	// Case 2: `export VAR=value` or `export VAR`
	i = 1;
	while (args[i])
	{
		arg = args[i];
		eq_ptr = ft_strchr(arg, '=');

		if (eq_ptr == arg) // `export =value` is invalid
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(arg, STDERR_FILENO);
			ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
			ret_status = 1;
			i++;
			continue;
		}
		
		if (eq_ptr) // Argument is of the form NAME=value
		{
			name = ft_strdup(arg); // Duplicate to modify
			if (!name) return (1); // Malloc error
			name[eq_ptr - arg] = '\0'; // Null-terminate the name part
			value = eq_ptr + 1;

			if (!is_valid_identifier(name))
			{
				ft_putstr_fd("minishell: export: `", STDERR_FILENO);
				ft_putstr_fd(name, STDERR_FILENO); // Print the problematic name part
				ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
				ret_status = 1;
			}
			else
			{
				if (my_setenv(name, value, env_ptr) != 0)
				{
					// my_setenv failed (e.g., malloc error inside it)
					ret_status = 1; // Or handle specific error from my_setenv
				}
			}
			free(name);
		}
		else // Argument is of the form NAME (no '=' sign)
		{
			name = arg;
			if (!is_valid_identifier(name))
			{
				ft_putstr_fd("minishell: export: `", STDERR_FILENO);
				ft_putstr_fd(name, STDERR_FILENO);
				ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
				ret_status = 1;
			}
			else
			{
				// If NAME already exists, POSIX export does nothing.
				// If it doesn't exist, some shells add it with no value.
				// For Minishell, if it's a valid identifier and not already in env,
				// you might add it as NAME="" or NAME (if my_setenv can handle NULL value).
				// Or, if all vars in your env_ptr are considered "exported", just do nothing.
				// Let's assume for now: if valid and not there, add as NAME=""
				if (!my_getenv(name, *env_ptr))
				{
					if (my_setenv(name, "", env_ptr) != 0)
						ret_status = 1;
				}
			}
		}
		i++;
	}
	return (ret_status);
}
