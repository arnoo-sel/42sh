/*
** set_var.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
**
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Fri Jun  6 11:03:13 2008 arnaud sellier
** Last update Wed Jun 11 13:24:11 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

t_env	*init_var()
{
  t_env	*var;

  var = xsmalloc(sizeof(*var));
  var[0].name = NULL;
  return (var);
}

void	new_var_alr_exist(int len, int id, t_param *param, char **cmd)
{
  t_env	*new;
  int	pos;

  new = xsmalloc(sizeof(*new) * (id + 2));
  pos = -1;
  while (param->var[++pos].name != NULL)
    {
      new[pos].name = param->var[pos].name;
      new[pos].value = param->var[pos].value;
    }
  new[pos].name = my_strdup(cmd[1]);
  if (len == 3)
    new[pos].value = my_strdup(cmd[2]);
  else
    new[pos].value = NULL;
  new[++pos].name = NULL;
  xsfree(param->var);
  param->var = new;
}

void	new_var(int len, int id, t_param *param, char **cmd)
{
  if (param->var[id].name != NULL)
    {
      if (param->var[id].value != NULL)
	{
	  xsfree(param->var[id].value);
	  param->var[id].value = NULL;
	}
      if (len == 3)
	param->var[id].value = my_strdup(cmd[2]);
    }
  else
    new_var_alr_exist(len, id, param, cmd);
}

int	b_set(t_param *param, char **cmd)
{
  int	id;
  int	len;

  len = 0;
  while (cmd[len] != NULL)
    len++;
  if (len == 0);
  else if (len > 3)
    my_printf("set: Too many arguments.\n");
  else if (len == 1)
    disp_alias(param->var);
  else if (len == 3)
    {
      id = 0;
      while ((param->var[id].name != NULL)
	     && (my_strcmp(param->var[id].name, cmd[1])))
	id++;
      new_var(len, id, param, cmd);
    }
  else
    my_printf("set: Too few arguments.\n");
  return (0);
}
