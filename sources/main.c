
#include <shell.h>
#include <lexer.h>
#include <cmd_edit.h>

// static	void	print_hash(t_hashelem **path_tab)
// {
// 	t_hashelem	*tmp_list;
// 	int			i;

// 	i = 0;
// 	if (!path_tab)
// 		return ;
// 	tmp_list = NULL;
// 	while (i < 1021)
// 	{
// 		tmp_list = path_tab[i];
// 		while (tmp_list)
// 		{
// 			ft_putendl(tmp_list->bin_name);
// 			tmp_list = tmp_list->next;
// 		}
// 		i++;
// 	}
// }

// void		print_proc(t_process *proc)
// {
// 	if (!proc)
// 		return ;
// 	ft_putstr("proc cmd is : ");
// 	ft_putendl(proc->cmd);
// 	ft_putstr("proc fd 0 is : ");
// 	ft_putnbrendl(proc->fd[0]);	
// 	ft_putstr("proc fd 1 is : ");
// 	ft_putnbrendl(proc->fd[1]);	
// 	ft_putstr("proc fd 2 is : ");
// 	ft_putnbrendl(proc->fd[2]);
// 	while (proc->fd_to_close)
// 	{
// 		ft_putstr("we will close fd -> ");
// 		ft_putnbrendl(*((int *)(proc->fd_to_close->content)));
// 		proc->fd_to_close = proc->fd_to_close->next;
// 	}
// }

int				init_all(char **environ)
{
	t_ult		*ult;
	char		**cmd;
	int			i;

	ult = NULL;
	ult = init_ult(ult, environ);
	cmd = NULL;
	while (42)
	{
		i = 0;
		get_prompt(ult->env);
		termcap(ult);
		ft_putchar('\n');
		if (ult->cmd && *ult->cmd)
			cmd = ft_strsplit_tok(ult->cmd);
		// if (ult->cmd)
		// {
		// 	ult->ret = search_for_builtins(ult);
		// 	if (!ft_strcmp(ult->cmd, "hash") && ult->hash_table)
		// 		print_hash(ult->hash_table);
		// }
		if (ult->cmd && *ult->cmd)
		{
			if (cmd[i])
				start_prog(ult, cmd);
		}
		ult->cmd ? ft_strdel(&ult->cmd) : NULL;
		free_tab(cmd);
		cmd = NULL;
	}
	return (0);
}

int				main(int ac, char **av, char **environ)
{
	av = NULL;
	(void)av;
	if (ac != 1)
	{
		ft_putendl_fd("error: 21sh requires no arguments", 2);
		exit(-1);
	}
	init_all(environ);
	return (0);
}
