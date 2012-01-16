/*
** set_alias.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src/builtins
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Thu Jun  5 14:38:08 2008 jocelyn de-la-rosa
** Last update Thu Jun 12 11:42:38 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

t_env	*init_alias()
{
  t_env	*alias;

  alias = xsmalloc(sizeof(*alias));
  alias[0].name = NULL;
  return (alias);
}

void	new_alias_alr_exist(int len, int id, t_param *param, char **cmd)
{
  t_env	*new;
  int	pos;

  new = xsmalloc(sizeof(*new) * (id + 2));
  pos = -1;
  while (param->alias[++pos].name != NULL)
    {
      new[pos].name = param->alias[pos].name;
      new[pos].value = param->alias[pos].value;
    }
  new[pos].name = my_strdup(cmd[1]);
  if (len == 3)
    new[pos].value = my_strdup(cmd[2]);
  else
    new[pos].value = NULL;
  new[++pos].name = NULL;
  xsfree(param->alias);
  param->alias = new;
}

void	new_alias(int len, int id, t_param *param, char **cmd)
{
  if (param->alias[id].name != NULL)
    {
      if (param->alias[id].value != NULL)
	{
	  xsfree(param->alias[id].value);
	  param->alias[id].value = NULL;
	}
      if (len == 3)
	param->alias[id].value = my_strdup(cmd[2]);
    }
  else
    new_alias_alr_exist(len, id, param, cmd);
}

void	disp_alias(t_env *alias)
{
  int	id;

  id = -1;
  while (alias[++id].name)
    {
      if (alias[id].value == NULL)
	my_printf("%s=\n", alias[id].name);
      else
	my_printf("%s\t%s\n", alias[id].name, alias[id].value);
    }
}

int	b_alias(t_param *param, char **cmd)
{
  int	id;
  int	len;

  len = 0;
  while (cmd[len] != NULL)
    len++;
  if (len == 0);
  else if (len > 3)
    my_printf("alias: Too many arguments.\n");
  else if (len == 1)
    disp_alias(param->alias);
  else if (len == 3)
    {
      id = 0;
      while ((param->alias[id].name != NULL)
	     && (my_strcmp(param->alias[id].name, cmd[1])))
	id++;
      new_alias(len, id, param, cmd);
    }
  else
    disp_alias_value(param, cmd[1]);
  return (0);
}
