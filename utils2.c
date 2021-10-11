#include "pipex.h"

int	ft_numwords(char const *s, char c)
{
	int				words;
	unsigned int	i;

	i = 0;
	words = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
			words++;
		while (s[i] && (s[i] != c))
			i++;
	}
	return (words);
}

void	ft_cancel_arr(char **mass)
{
	while (*mass)
	{
		free(*mass);
		mass++;
	}
	free(mass);
}

char	*ft_strdup(const char *s)
{
	size_t	l;
	size_t	i;
	char	*new;

	l = 0;
	i = 0;
	while (s[l])
		l++;
	new = (char *)malloc(l * sizeof(char) + 1);
	if (!new)
		return (NULL);
	while (i < l)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	exec_err(char *cmd, char *err, int ex)
{
	write(2, cmd, ft_strlen(cmd));
	write(2, err, ft_strlen(err));
	exit(ex);
}
