/*
** variable.c for 42sh in /u/epitech_2012/jartho_d/cu/public/perso/42sh/mysh
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Fri Jun  6 10:13:14 2008 adrien1 jarthon
** Last update Wed Jun 11 13:35:08 2008 adrien1 jarthon
*/

#include "42sh.h"

char	*put_var(t_param *param, char *str)
{
  int	var;
  char	*name;

  var = -1;
  while (param->var[++var].name)
    {
      name = xsmalloc(sizeof(*name) * (my_strlen(param->var[var].name) + 2));
      name[0] = DOLLAR;
      my_strcpy(name + 1, param->var[var].name);
      str = my_str_replace(str, name, param->var[var].value);
      xsfree(name);
    }
  return (str);
}

char	*put_env_var(t_param *param, char *str)
{
  int	var;
  char	*name;

  var = -1;
  while (param->env[++var].name)
    {
      name = xsmalloc(sizeof(*name) * (my_strlen(param->env[var].name) + 2));
      name[0] = DOLLAR;
      my_strcpy(name + 1, param->env[var].name);
      str = my_str_replace(str, name, param->env[var].value);
      xsfree(name);
    }
  return (str);
}

void	variables_substitution(t_param *param, t_pipeline *pipeline)
{
  int	id;
  int	pos;
  char	*inhib;

  id = -1;
  while (pipeline->cmd[++id])
    {
      inhib = xsmalloc(sizeof(*inhib) * (my_strlen(pipeline->cmd[id]) + 1));
      memset(inhib, 4, my_strlen(pipeline->cmd[id]));
      pos = -1;
      while (pipeline->cmd[id][++pos])
	if ((pipeline->cmd[id][pos] == '$') &&
	    !(is_inhibited(pipeline->cmd[id], inhib, pos)))
	  pipeline->cmd[id][pos] = DOLLAR;
      pipeline->cmd[id] = put_var(param, pipeline->cmd[id]);
      pipeline->cmd[id] = put_env_var(param, pipeline->cmd[id]);
      pos = -1;
      my_char_replace(pipeline->cmd[id], DOLLAR, '$');
      xsfree(inhib);
    }
}
