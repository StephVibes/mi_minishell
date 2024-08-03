#include "../../includes/minishell.h"


char **quotes_expand(char **str, t_env *env_list)
{
	int	i;
	char *processed_str;

	i = 0;
	while(str[i])
	{
		processed_str = handle_quoting(str[i], env_list);
		str[i] = processed_str;
		i++;
	}
	return(str);
}

void	what_builtin(char **command_words, t_env *env_list)
{
    size_t len;

    len = ft_strlen(command_words[0]);
    if(!ft_strncmp(command_words[0], "echo", len))
	 	echo(command_words, env_list);
	if(!ft_strncmp(command_words[0], "cd", len))
	 	cd(command_words[1]);
	if(!ft_strncmp(command_words[0], "pwd", len))
		pwd();
	// if(!ft_strncmp(command_words, "export", len))
	// 	export();
	// if(!ft_strncmp(command_words, "unset", len))
	// 	unset();
	if(!ft_strncmp(command_words[0], "env", len))
	 	cmd_env(env_list);
	// if(!ft_strncmp(command_words, "exit", len))
	// 	exit();
}