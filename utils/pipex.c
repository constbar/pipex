#include "../pipex.h"

int	main(int argc, char *argv[], char *env[])
{
	int		read_fd;
	int		write_fd;
	char	*full_cmd[2];

	if (argc != 5)
		exec_err(NULL, "please, give me f1 cmd1 cmd2 f2\n", 1);
	read_fd = open(argv[1], O_RDONLY);
	if (read_fd == -1)
		exec_err(argv[1], ": No such file or directory or no permission\n", 1);
	write_fd = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (write_fd == -1)
		exec_err(argv[1], ": Can not open the file or no permission\n", 1);
	full_cmd[0] = argv[2];
	full_cmd[1] = argv[3];
	pipe_handler(&*full_cmd, read_fd, write_fd, env);
	close(read_fd);
	close(write_fd);
	return (0);
}

static void	pipe_help(int i, int *pipes, int re, int wr)
{
	if (i > 0)
		dup2(pipes[0], STDIN_FILENO);
	else if (re)
	{
		dup2(re, STDIN_FILENO);
		close(re);
	}
	if (i < 1)
		dup2(pipes[1], STDOUT_FILENO);
	else if (wr)
	{
		dup2(wr, STDOUT_FILENO);
		close(wr);
	}
	close(pipes[0]);
	close(pipes[1]);
}

void	pipe_handler(char **full_cmd, int re, int wr, char **env)
{
	int		i;
	pid_t	pid;
	int		status;
	int		pipes[2];

	i = -1;
	if (pipe(pipes) == -1)
		exit(86);
	while (++i < 2)
	{
		pid = fork();
		if (pid < 0)
			exit(10);
		else if (pid == 0)
		{
			pipe_help(i, pipes, re, wr);
			exec_cmd(ft_split(full_cmd[i], ' '), env);
		}
		else if (i == 1)
		{
			close(pipes[0]);
			close(pipes[1]);
			waitpid(pid, &status, 0);
		}
	}
}

static void	exec_helper(char **part, char **list_cmd, char **env)
{
	char	*tmp;

	tmp = ft_strjoin(*part, "/");
	free(*part);
	*part = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strjoin(*part, list_cmd[0]);
	execve(tmp, list_cmd, env);
	free(tmp);
}

void	exec_cmd(char **list_cmd, char **env)
{
	int		i;
	char	*tmp;
	char	**parts;
	int		size_parts;

	if (!list_cmd[0])
		exec_err(NULL, "Command '' not found\n", 127);
	i = 0;
	size_parts = 0;
	tmp = get_path(env);
	if (!tmp)
		exit(1);
	parts = ft_split(tmp, ':');
	while (parts[size_parts])
		size_parts++;
	check_sl_join(parts, list_cmd, env);
	while (i < size_parts)
	{
		exec_helper(&parts[i], list_cmd, env);
		i++;
	}
	exec_err(list_cmd[0], ": command not found\n", 127);
}
