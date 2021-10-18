#include "../pipex.h"

char	*get_path(char **env)
{
	int		i;
	char	*tmp;

	i = 0;
	while (env[i])
	{
		if (!(ft_strncmp(env[i], "PATH=", 5)))
		{
			tmp = ft_substr(env[i], 5, ft_strlen(env[i]) - 1);
			return (tmp);
		}
		i++;
	}
	return (NULL);
}

void	check_sl_join(char **parts, char **list_cmd, char **env)
{
	int		i;
	int		cmp;
	char	*tmp;

	if (!list_cmd[0])
		exit(1);
	if (list_cmd[0][0] == '.' && list_cmd[0][1] == '/')
		execve(list_cmd[0], list_cmd, env);
	i = 0;
	while (parts[i])
	{
		tmp = ft_strjoin(parts[i], "/");
		cmp = ft_strncmp(tmp, list_cmd[0], ft_strlen(tmp) - 10);
		if (!cmp)
			execve(list_cmd[0], list_cmd, env);
		free(tmp);
		i++;
	}
}
