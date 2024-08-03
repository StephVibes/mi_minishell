#include "../../includes/minishell.h"
//TODO eliminate quotes in the string if any
//TODO handle escape characters
void	echo(char **str)
{
	int	i;
	size_t	len;
	//char *processed_str;

	i = 1;
	//processed_str = NULL;
	if(str[i])
	{
		len = ft_strlen(str[1]);
		if(ft_strncmp(str[1], "-n", len) == 0)
			i++;
		while(str[i])
		{
			//processed_str = handle_quoting(str[i], env_list);
			printf("%s", str[i]);
			if(str[i + 1] != NULL)
				printf(" ");
			//free(processed_str);
			i++;
		}
		if(ft_strncmp(str[1], "-n", len) != 0)
			printf("\n");
	}
}