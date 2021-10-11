#include "pipex.h"

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	ft_memset(p, '\0', n);
}

static void	*ft_calloc(size_t n, size_t size)
{
	void	*p;

	p = (void *)malloc(n * size);
	if (!p)
		return (NULL);
	ft_bzero(p, size * n);
	return (p);
}

static char	**ft_fill(char **res, int i, char const *s, char c)
{
	int			letters;
	char const	*s2;

	letters = 0;
	s2 = s;
	while (*s && *s != c)
	{
		letters++;
		s++;
	}
	res[i] = (char *)ft_calloc(letters + 1, sizeof(char));
	if (!res[i])
		ft_cancel_arr(res);
	letters = 0;
	while (*s2 && *s2 != c)
	{
		res[i][letters] = *s2;
		letters++;
		s2++;
	}
	return (res);
}

void	*ft_memset(void *str, int c, size_t n)
{
	while (n--)
		*(unsigned char *)(str + n) = c;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		numwords;
	char	**final_res;

	if (!s)
		return (NULL);
	numwords = ft_numwords(s, c);
	final_res = (char **)ft_calloc(numwords + 1, sizeof(char *));
	if (!final_res)
		return (NULL);
	i = 0;
	while (*s)
	{
		if (*s == c)
			while (*s && *s == c)
				s++;
		else
		{
			final_res = ft_fill(final_res, i, s, c);
			while (*s && *s != c)
				s++;
			i++;
		}
	}
	return (final_res);
}
