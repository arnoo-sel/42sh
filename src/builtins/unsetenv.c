/*
** unsetenv.c for unsetenv in /home/farges_y/cunix/42sh/mysh
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Tue May  6 15:58:36 2008 yoam farges
** Last update Thu Jun  5 16:54:32 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

int	check_exist_unsetenv(char *str, t_env *env)
{
  int	id;

  id = 0;
  while (env[id].name != NULL)
    {
      if (my_strcmp(env[id].name, str) == 0)
	return (id);
      id++;
    }
  return (-1);
}

void	remove_unsetenv(t_param *param, int pos)
{
  t_env	*new;
  int	id;
  int	id_new;

  id = 0;
  while (param->env[id].name != NULL)
    id++;
  new = xsmalloc(sizeof(*new) * (id));
  id = -1;
  id_new = 0;
  while (param->env[++id].name != NULL)
    {
      if (id != pos)
	{
	  new[id_new].name = param->env[id].name;
	  new[id_new].value = param->env[id].value;
	  id_new++;
	}
    }
  new[id_new].name = NULL;
  xsfree(param->env);
  param->env = new;
}

int	b_unsetenv(t_param *param, char **cmd)
{
  int	len;
  int	pos;

  len = 0;
  while (cmd[len] != NULL)
    len++;
  if (len <= 1)
    my_printf("unsetenv: Too few arguments.\n");
  else
    {
      len = 1;
      while (cmd[len] != NULL)
	{
	  if ((pos = check_exist_unsetenv(cmd[len], param->env)) != -1)
	    remove_unsetenv(param, pos);
	  len++;
	}
    }
  return (0);
}
