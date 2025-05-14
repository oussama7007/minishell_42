/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oadouz <oadouz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:05:55 by oadouz            #+#    #+#             */
/*   Updated: 2025/05/14 18:27:10 by oadouz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_structs.h"
#include "../built_functions.h"

/*
NB: Ensure your libft (or equivalent) provides:
ft_strlen, ft_strchr, ft_strncmp, ft_strdup, ft_substr, ft_strjoin_gnl (robust),
ft_putstr_fd, ft_putchar_fd, ft_strcmp.
And your environment manipulation functions (my_setenv, my_getenv)
and display_sorted_environment are implemented as described above.
g_shell_status should be your global variable for exit status.
*/

// --- Assumed global for exit status ---
// extern int g_shell_status; // You need to manage this

// --- Utility Functions (Norminette Compliant) ---

// Strips a single layer of outermost matching quotes ("" or '')
// Returns a new string that caller must free.
// Returns ft_strdup(str) if no surrounding quotes or if str is NULL/empty.
// Forward declaration if not in a header yet:
// char	*strip_outer_quotes(const char *str);
// void	print_one_export_var(char *env_var_copy); // Assuming this exists and is correct
// void	display_sorted_environment(char **envp); // Assuming this exists





// For 'export NAME=VALUE'
int	exec_export_value(const char *arg, char ***env_ptr)
{
	char	*name;
	char	*value_ptr;
	char	*actual_value;
	char	*stripped_value;
	int		status;

	value_ptr = ft_strchr(arg, '='); // Already know '=' is present
	if (value_ptr == arg) // Starts with '=', e.g., "=value"
	{
		char *val_for_err;
		char *err_str;
		val_for_err = strip_outer_quotes(value_ptr + 1);
		err_str = ft_strjoin("=", val_for_err);
		print_err_export(NULL, err_str);
		free(val_for_err);
		free(err_str);
		return (1);
	}
	name = ft_substr(arg, 0, value_ptr - arg);
	if (!name)
		return (1); // Malloc error
	if (!is_valid_identifier(name))
	{
		print_err_export(NULL, name);
		free(name);
		return (1);
	}
	actual_value = value_ptr + 1;
	stripped_value = strip_outer_quotes(actual_value);
	if (!stripped_value)
	{
		free(name);
		return (1); // Malloc error in strip_outer_quotes
	}
	status = my_setenv(name, stripped_value, env_ptr);
	free(name);
	free(stripped_value);
	return (status);
}

// For 'export NAME+=VALUE'
int	exec_export_plus_equal(const char *arg, char ***env_ptr)
{
	char	*name;
	char	*plus_equal_ptr;
	char	*value_to_append_original;
	char	*value_to_append_stripped;
	char	*old_val;
	char	*new_val_str;
	int		status;

	plus_equal_ptr = ft_strnstr(arg, "+=", ft_strlen(arg)); // Know "+=" is there
	name = ft_substr(arg, 0, plus_equal_ptr - arg);
	if (!name)
		return (1); // Malloc error

	if (name[0] == '\0') // Starts with "+=", e.g., "+=value"
	{
		char *val_for_err;
		char *err_str;

		val_for_err = strip_outer_quotes(plus_equal_ptr + 2);
		err_str = ft_strjoin("+=", val_for_err);
		print_err_export(NULL, err_str);
		free(val_for_err);
		free(err_str);
		free(name); // Name was "" but still allocated
		return (1);
	}
	if (!is_valid_identifier(name))
	{
		print_err_export(NULL, name);
		free(name);
		return (1);
	}
	value_to_append_original = plus_equal_ptr + 2;
	value_to_append_stripped = strip_outer_quotes(value_to_append_original);
	if (!value_to_append_stripped)
	{
		free(name);
		return (1); // Malloc error in strip_outer_quotes
	}
	old_val = my_getenv(name, *env_ptr);
	if (old_val == NULL) // Var doesn't exist or has no value (e.g. declare -x VAR)
	{
		// Treat as new assignment: NAME=VALUE (where VALUE is value_to_append_stripped)
		new_val_str = ft_strdup(value_to_append_stripped);
	}
	else
	{
		new_val_str = ft_strjoin(old_val, value_to_append_stripped);
		// my_getenv might return "" if var was 'NAME='. ft_strjoin(old_val,"") is fine.
	}
	if (!new_val_str)
	{
		free(name);
		free(value_to_append_stripped);
		// old_val is not heap-allocated by my_getenv, so no free(old_val)
		return (1); // Malloc error for new_val_str
	}
	status = my_setenv(name, new_val_str, env_ptr);
	free(name);
	free(value_to_append_stripped);
	free(new_val_str);
	return (status);
}

int	process_export_arguments(char **args, char ***env_ptr)
{
	int		i;
	int		ret_status;
	char	*current_arg;
	char	*equal_sign;
	char	*plus_equal_sign;

	i = 1;
	ret_status = 0;
	while (args[i])
	{
		current_arg = args[i];
		// IMPORTANT: Your main parser's tokenization determines what current_arg is.
		// If parser gives "NAME+=VALUE" as one token, this logic is fine.
		// If parser gives "NAME", "+=", "VALUE" as separate tokens, this will break
		// and needs a more stateful parser in process_export_arguments.
		// The following assumes "NAME+=VALUE" or "NAME=VALUE" can be single args.
		plus_equal_sign = ft_strnstr(current_arg, "+=", ft_strlen(current_arg));
		equal_sign = ft_strchr(current_arg, '=');

		if (plus_equal_sign && (plus_equal_sign + 1 == equal_sign)) // Catches "NAME+="
			ret_status |= exec_export_plus_equal(current_arg, env_ptr);
		else if (equal_sign) // Catches "NAME="
			ret_status |= exec_export_value(current_arg, env_ptr);
		else // No '=' or '+=' in the argument, treat as 'export NAME'
			ret_status |= exec_export_name_only(current_arg, env_ptr);
		i++;
	}
	return (ret_status);
}

int	ft_export(char **args, char ***env_ptr)
{
	if (!env_ptr || !(*env_ptr)) // Should not happen if env is initialized
		return (1);
	if (!args[1]) // 'export' with no arguments
	{
		display_sorted_environment(*env_ptr);
		return (0);
	}
	return (process_export_arguments(args, env_ptr));
}
