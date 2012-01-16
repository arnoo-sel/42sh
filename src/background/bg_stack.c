/*
** bg_stack.c for 42sh in /u/epitech_2012/jartho_d/cu/public/perso/42sh/mysh
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Tue Jun 10 11:46:57 2008 adrien1 jarthon
** Last update Wed Jun 11 15:30:43 2008 adrien1 jarthon
*/

#include "42sh.h"

void		bg_stack(t_param *param, int pid, char *cmd)
{
  t_bg_item	*item;

  item = xsmalloc(sizeof(*item));
  item->pid = pid;
  item->cmd = my_strdup(cmd);
  my_printf("Background [%d] : '%s'\n", pid, cmd);
  vector_push(param->bg_table, (void*)item);
}

void		disp_term_info(int status, int pid, char *cmd)
{
  if (WIFEXITED(status))
    {
      if (WEXITSTATUS(status))
	my_printf("Exit %d [%d] : '%s'\n", WEXITSTATUS(status),
		  pid, cmd);
      else
	my_printf("Done [%d] : '%s'\n", pid, cmd);
    }
  if (WIFSIGNALED(status))
    my_printf("%s%d] : '%s'\n",disp_signal_name(WTERMSIG(status)), pid, cmd);
}

void		bg_unstack(t_param *param)
{
  t_bg_item	*item;
  int		id;
  int		status;
  int		ret;

  id = -1;
  while (++id < vector_size(param->bg_table))
    {
      if (!(item = param->bg_table->data[id]))
	continue;
      ret = waitpid(item->pid, &status, WNOHANG);
      if (param->debug)
	my_printf("%[3]bg: %[]%s [%d]: status = %d ret = %d\n",
		  item->cmd, item->pid, status, ret);
      if (ret == 0)
	continue;
      disp_term_info(status, item->pid, item->cmd);
      msfree(item->cmd, item, 0);
      param->bg_table->data[id] = 0;
    }
}
