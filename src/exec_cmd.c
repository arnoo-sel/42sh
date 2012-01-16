/*
** exec_cmd.c for 42sh in /u/epitech_2012/jartho_d/cu/public/perso/42sh/mysh
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Wed May  7 09:54:52 2008 adrien1 jarthon
** Last update Fri Jun 13 13:05:16 2008 yoam farges
*/

#include "42sh.h"

int	exec_builtins(t_param *param, t_cmd *cmd)
{
  int	id;

  id = 0;
  while (id < NB_BUILTINS)
    {
      if (my_strcmp(param->f_built[id].name, cmd->arg[0]) == 0)
	{
	  cmd->status = param->f_built[id].func(param, cmd->arg);
	  return (1);
	}
      id++;
    }
  return (0);
}

void	exec_cmd_low_level(t_param *param, t_cmd *cmd)
{
  char  *path;
  char  *cmd_path;

  if (my_strstr(cmd->arg[0], "/") == 0)
    {
      while ((path = get_next_path(param->env)))
        {
          cmd_path = xsmalloc(my_strlen(path) + my_strlen(cmd->arg[0]) + 2);
          my_strcpy(cmd_path, path);
          my_strcat(cmd_path, "/");
          my_strcat(cmd_path, cmd->arg[0]);
          xsfree(path);
          if (access(cmd_path, F_OK) != -1)
            execve(cmd_path, (cmd->arg), environ);
          xsfree(cmd_path);
        }
      my_fprintf(2, "%s: command not found\n", cmd->arg[0]);
    }
  else
    {
      execve(cmd->arg[0], cmd->arg, environ);
      my_fprintf(2, "%s: can't exec\n", cmd->arg[0]);
    }
  free_all(param);
  exit(1);
}

void		exec_cmd(t_param *param, t_cmd *cmd)
{
  int		pid;
  t_fd		save;

  if ((param->tty) && (param->debug))
    my_fprintf(2, "%[3]Exec command `%S' io [%d %d %d] %[]\n",
	       cmd->arg[0], cmd->in.fd, cmd->out.fd, cmd->err.fd);
  if (replace_tild(param, cmd))
    return;
  if (globing_substitution(cmd))
    return;
  SAVE_FD;
  DUP_FD;
  if (exec_builtins(param, cmd))
    cmd->pid = PID_BUILTIN;
  else if ((pid = fork()))
    cmd->pid = pid;
  else
    exec_cmd_low_level(param, cmd);
  RESTOR_FD;
  return;
}

void		set_last_state(t_param *param, int state)
{
  char		*cmd[4];

  cmd[0] = "set";
  cmd[1] = "?";
  cmd[2] = xsmalloc(10);
  cmd[3] = 0;
  memset(cmd[2], 0, 10);
  my_putnbr_base(state, "0123456789", cmd[2]);
  b_set(param, cmd);
  xsfree(cmd[2]);
}
