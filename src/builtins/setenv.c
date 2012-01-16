/*
** setenv.c for setenv in /home/farges_y/link/42sh/mysh/src/builtins
** 
** Made by yoam farges
** Login   <farges_y@epitech.net>
** 
** Started on  Tue May  6 10:49:52 2008 yoam farges
** Last update Thu Jun  5 13:13:14 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

void	new_setenv_alr_exist(int len, int id, t_param *param, char **cmd)
{
  t_env	*new;
  int	pos;

  new = xsmalloc(sizeof(*new) * (id + 2));
  pos = -1;
  while (param->env[++pos].name != NULL)
    {
      new[pos].name = param->env[pos].name;
      new[pos].value = param->env[pos].value;
    }
  new[pos].name = my_strdup(cmd[1]);
  if (len == 3)
    new[pos].value = my_strdup(cmd[2]);
  else
    new[pos].value = NULL;
  new[++pos].name = NULL;
  xsfree(param->env);
  param->env = new;
}

void	new_setenv(int len, int id, t_param *param, char **cmd)
{
  if (param->env[id].name != NULL)
    {
      if (param->env[id].value != NULL)
	{
	  xsfree(param->env[id].value);
	  param->env[id].value = NULL;
	}
      if (len == 3)
	param->env[id].value = my_strdup(cmd[2]);
    }
  else
    new_setenv_alr_exist(len, id, param, cmd);
}

int	b_setenv(t_param *param, char **cmd)
{
  int	id;
  int	len;

  len = 0;
  while (cmd[len] != NULL)
    len++;
  if (len == 0);
  else if (len > 3)
    my_printf("setenv: Too many arguments.\n");
  else if (len == 1)
    b_env(param, cmd);
  else if (strchr(cmd[1], '=') != 0)
    my_printf("setenv: Syntax Error.\n");
  else
    {
      id = 0;
      while ((param->env[id].name != NULL)
	     && (my_strcmp(param->env[id].name, cmd[1])))
	id++;
      new_setenv(len, id, param, cmd);
    }
  return (0);
}
