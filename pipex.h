#ifndef PIPEX_H
# define PIPEX_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>

int		ft_putchar(int c);
void	ft_putstr(char *s);
char	*get_path(char **env);
char	*ft_strdup(const char *s);
void	ft_cancel_arr(char **mass);
size_t	ft_strlen(const char *str);
char	**ft_split(char const *s, char c);
int		ft_numwords(char const *s, char c);
void	exec_cmd(char **list_cmd, char **env);
void	*ft_memset(void *str, int c, size_t n);
void	exec_err(char *cmd, char *err, int ex);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
void	check_sl_join(char **parts, char **list_cmd, char **env);
void	pipe_handler(char **full_cmd, int re, int wr, char **env);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
