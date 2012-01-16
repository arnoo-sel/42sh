/*
** alias_substitution.c for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src
** 
** Made by jocelyn de-la-rosa
** Login   <de-la-_o@epitech.net>
** 
** Started on  Mon Jun  9 10:53:55 2008 jocelyn de-la-rosa
** Last update Fri Jun 13 12:43:42 2008 jocelyn de-la-rosa
*/

#include "42sh.h"

int	clear_space_tab(char *str, int i)
{
  if ((str[i] != '\0') && (str[i + 1] != '\0') && (i != 0))
    i++;
  if ((str[i] != '\0') && (str[i + 1] != '\0') && ((str[i] == '|') ||
			       (str[i] == '&')))
    i++;
  while ((str[i] != '\0') && (str[i + 1] != '\0') && ((str[i] == ' ')
						      || (str[i] == '\t')))
    i++;
  return (i);
}

char	*replace_alias(char *line, char *alias, int i, int name_len)
{
  char	*cmd;
  int	alias_len;
  int	line_len;
  int	id;

  line_len = my_strlen(line);
  alias_len = my_strlen(alias);
  cmd = xsmalloc(sizeof(*cmd) * (alias_len + line_len + 1));
  my_memset(cmd, 0,  alias_len + line_len + 1);
  id = 0;
  my_strncpy(cmd, line, i);
  i += name_len;
  cmd = my_strcat(cmd, alias);
  cmd = my_strcat(cmd, line + i);
  xsfree(line);
  return (cmd);
}

int	check_alias(t_param *param, int alias_len, int i, int id)
{
  if (!my_strncmp(param->line + i,
		  param->alias[id].name, alias_len)
      && ((param->line[i + alias_len] == '\0' ) ||
	  (param->line[i + alias_len] == '\t') ||
	  (param->line[i + alias_len] == '|') ||
	  (param->line[i + alias_len] == ';') ||
	  (param->line[i + alias_len] == '&') ||
	  (param->line[i + alias_len] == ' ')))
    return (1);
  return (0);
}

int	alias_substitution(t_param *param)
{
  int	i;
  int	id;
  int	alias_len;

  i = -1;
  while (param->line[++i])
    {
      id = 0;
      if ((i == 0) || (param->line[i] == '|') ||
	  (param->line[i] == '&') || (param->line[i] == ';'))
	{
	  i = clear_space_tab(param->line, i);
	  while (param->alias[id].name)
	    {
	      alias_len = my_strlen(param->alias[id].name);
	      if (check_alias(param, alias_len, i, id))
		  param->line = replace_alias(param->line,
					      param->alias[id].value,
					      i, alias_len);
	      id++;
	    }
	}
    }
  return (0);
}
