/*
** unalias.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src/builtins
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Thu Jun  5 16:09:54 2008 jocelyn de-la-rosa
** Last update Mon Jun  9 17:04:31 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

int	check_exist_unalias(char *str, t_env *alias)
{
  int	id;

  id = 0;
  while (alias[id].name != NULL)
    {
      if (my_strcmp(alias[id].name, str) == 0)
	return (id);
      id++;
    }
  return (-1);
}

void	remove_unalias(t_param *param, int pos)
{
  t_env	*new;
  int	id;
  int	id_new;

  id = 0;
  while (param->alias[id].name != NULL)
    id++;
  new = xsmalloc(sizeof(*new) * (id));
  id = -1;
  id_new = 0;
  while (param->alias[++id].name != NULL)
    {
      if (id != pos)
	{
	  new[id_new].name = param->alias[id].name;
	  new[id_new].value = param->alias[id].value;
	  id_new++;
	}
    }
  new[id_new].name = NULL;
  xsfree(param->alias);
  param->alias = new;
}

int	b_unalias(t_param *param, char **cmd)
{
  int	len;
  int	pos;

  len = 0;
  while (cmd[len] != NULL)
    len++;
  if (len <= 1)
    my_printf("unalias: Too few arguments.\n");
  else
    {
      len = 1;
      while (cmd[len] != NULL)
	{
	  if ((pos = check_exist_unalias(cmd[len], param->alias)) != -1)
	    remove_unalias(param, pos);
	  len++;
	}
    }
  return (0);
}
