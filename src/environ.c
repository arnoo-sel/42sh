/*
** environ.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Mon May  5 11:48:02 2008 jocelyn de-la-rosa
** Last update Tue May 27 13:32:36 2008 adrien1 jarthon
*/

#include "42sh.h"

t_env	*malloc_env(void)
{
  int	len;
  t_env	*env;

  len = -1;
  while (environ[++len]);
  env = xsmalloc(sizeof(*env) * (len + 1));
  return (env);
}

char	*env_var_name(char *line)
{
  int	len;
  char	*name;

  len = -1;
  while (line[++len] != '=');
  name = xsmalloc(sizeof(*name) * (len + 1));
  my_strncpy(name, line, len);
  name[len] = '\0';
  return (name);
}

char	*env_var_value(char *line)
{
  int	id;
  char	*value;

  id = 0;
  while (line[id++] != '=');
  value = xsmalloc(sizeof(*value) * (my_strlen(line + id) + 1));
  my_strcpy(value, line + id);
  return (value);
}

int	init_env(t_param *param)
{
  int	id;
  t_env	*env;

  env = malloc_env();
  id = -1;
  while (environ[++id])
    {
      env[id].value = env_var_value(environ[id]);
      env[id].name = env_var_name(environ[id]);
    }
  env[id].name = NULL;
  param->env = env;
  return (0);
}
