#include "../../includes/minishell.h"
//TODO eliminate quotes in the string if any

char	*check_for_var(char *str, t_env *env_list)
{
	int	i;
	int j;
	char *var_name;
	char *value;
	t_env *current;

	i = 0;
	value = NULL;
	current = env_list;
	while(str[i])
	{
		if(str[i] == '$' && str[i + 1])
		{
			i++;
			j = i;
			while(ft_isalnum(str[i]) && str[i])
				i++;
			var_name = ft_substr(str, j, i - j);
			while(current)
			{
				if(ft_strncmp(var_name, current->key, i - j) == 0)
				{
					value = ft_strdup(current->value);
					free(var_name);
					return(value);
				}
				current = current->next;
			}
			if(value == NULL)
				return(ft_strdup(""));
		}
		else
			i++;
	}
	return(NULL);
}

char	*expand_var(char *str, t_env *env_list)
{
	int	i;
	int j;
	int k;
	size_t expanded_len;
	char *var_name;
	char *value;
	char *result;

	i = 0;
	j = 0;
	k = 0;
	value = NULL;
	expanded_len = calc_expanded_len(str, env_list);
	result = (char *)malloc(expanded_len + 1);
	if(!result)
		return(NULL);
	while(str[i])
	{
		if(str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			j = i;
			while(ft_isalnum(str[i]) || str[i] == '_')
				i++;
			var_name = ft_substr(str, j, i - j);
			value = find_env_value(var_name, env_list, i - j);
			free(var_name);
			if(value)
			{
				while(*value)
				{
					result[k++] = *value++;
				}
			}
		}
		else
		{
			result[k++] = str[i++];
		}
	}
	result[k] = '\0';
	return(result);
}

char	*handle_single_quotes(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	return(ft_substr(str, 1, len - 2));
}

char	*handle_double_quotes(char *str, t_env *env_list)
{
	size_t	len;
	char	*temp;
	char	*expanded;

	len = ft_strlen(str);
	temp = ft_substr(str, 1, len - 2);
        if (temp && check_for_var(temp, env_list))
		{
			expanded = expand_var(temp, env_list);
			if (expanded)
			{
        		free(temp);
            	temp = expanded;
        	}
		}
		return (temp);
}

char	*expand_variables(char *str, t_env *env_list)
{
	char	*temp;
	if (check_for_var(str, env_list))
	{
		temp = expand_var(str, env_list);
		if (temp)
        	return (temp);
	}
	return (NULL);
}

char	*handle_quoting(char *str, t_env *env_list)
{
	size_t len;
	char *quote_free;
	char *temp;

	len = ft_strlen(str);
	quote_free = ft_strdup(str);
	if (str[0] == '\'' && str[len - 1] == '\'')
		temp = handle_single_quotes(str);
    else if (str[0] == '"' && str[len - 1] == '"')
		temp = handle_double_quotes(str, env_list);
    else
		temp = expand_variables(quote_free, env_list);
	if (temp)
	{
		free(quote_free);
		quote_free = temp;
	}
	return (quote_free);
}

char	*find_env_value(char *key, t_env *env_list, size_t len)
{
	while(env_list)
	{
		if(ft_strncmp(key, env_list->key, len) == 0)
			return(env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

size_t	calc_expanded_len(char *str, t_env *env_list)
{
	size_t	len;
	int	i;
	int j;
	char	*var_name;
	char	*value;

	len = 0;
	i = 0;
	while(str[i])
	{
		if(str[i] == '$' && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			i++;
			j = i;
			while(ft_isalnum(str[i]) || str[i] == '_')
				i++;
			var_name = ft_substr(str, j, i - j);
			value = find_env_value(var_name, env_list, i - j);
			free(var_name);
			if(value)
				len += ft_strlen(value);
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	echo(char **str, t_env *env_list)
{
	int	i;
	size_t	len;
	char *processed_str;

	i = 1;
	processed_str = NULL;
	if(str[i])
	{
		len = ft_strlen(str[1]);
		if(ft_strncmp(str[1], "-n", len) == 0)
			i++;
		while(str[i])
		{
			processed_str = handle_quoting(str[i], env_list);
			printf("%s", processed_str);
			if(str[i + 1] != NULL)
				printf(" ");
			free(processed_str);
			i++;
		}
		if(ft_strncmp(str[1], "-n", len) != 0)
			printf("\n");
	}
}