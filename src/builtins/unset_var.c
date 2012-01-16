/*
** unset_var.c for 42sh.h in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Fri Jun  6 11:30:33 2008 arnaud sellier
** Last update Fri Jun  6 11:33:07 2008 arnaud sellier
*/

#include "42sh.h"

void	remove_unset(t_param *param, int pos)
{
  t_env	*new;
  int	id;
  int	id_new;

  id = 0;
  while (param->var[id].name != NULL)
    id++;
  new = xsmalloc(sizeof(*new) * (id));
  id = -1;
  id_new = 0;
  while (param->var[++id].name != NULL)
    {
      if (id != pos)
	{
	  new[id_new].name = param->var[id].name;
	  new[id_new].value = param->var[id].value;
	  id_new++;
	}
    }
  new[id_new].name = NULL;
  xsfree(param->var);
  param->var = new;
}

int	b_unset(t_param *param, char **cmd)
{
  int	len;
  int	pos;

  len = 0;
  while (cmd[len] != NULL)
    len++;
  if (len <= 1)
    my_printf("unset: Too few arguments.\n");
  else
    {
      len = 1;
      while (cmd[len] != NULL)
	{
	  if ((pos = check_exist_unalias(cmd[len], param->var)) != -1)
	    remove_unset(param, pos);
	  len++;
	}
    }
  return (0);
}
