/*
** str.c for 42sh in /home/jartho_d/42sh/mysh
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Mon May 26 14:38:50 2008 adrien1 jarthon
** Last update Mon Jun  9 15:38:33 2008 arnaud sellier
*/

#include "42sh.h"

char	*dir_from_vector(t_vector *dirs)
{
  char	*dir;
  int	i;

  dir = xsmalloc(BUF);
  my_strcpy(dir, "");
  i = 0;
  while (i < vector_size(dirs))
    my_strcat(dir, (char *)dirs->data[i++]);
  return (dir);
}

char	*complete_path(char *dir, char *file)
{
  char	*path;

  path = xsmalloc(my_strlen(dir) + my_strlen(file) + 1);
  my_strcpy(path, dir);
  my_strcat(path, file);
  return (path);
}

int	is_globbing(char **str)
{
  int	i;
  char	glob[] = "*?[]^{}";
  char	code[] = {STAR, ANY, OPEN_BRACKET, CLOSE_BRACKET,
		  HAT, OPEN_BRACE, CLOSE_BRACE, 0};
  char	*pos;
  int	type = 0;

  i = 0;
  while (str[0][i])
    {
      if ((pos = is_in(glob, str[0][i])) && (str[1][i] == 0))
	{
	  str[0][i] = code[pos - glob];
	  type = 1;
	}
      i++;
    }
  if (type)
    while ((pos = is_in(str[0], '-')) && (!str[1][pos - str[0]])
	   && (*is_in(str[0], '-') = DASH));
  return (type);
}

char	globbed_to_std(char c)
{
  char	glob[] = "*?[]^{}";
  char	code[] = {STAR, ANY, OPEN_BRACKET, CLOSE_BRACKET,
		  HAT, OPEN_BRACE, CLOSE_BRACE, 0};
  char	*pos;

  if ((pos = is_in(code, c)))
    return (glob[pos - code]);
  return (c);
}

int	my_globcmp(const void *d1, const void *d2)
{
  return (-my_strcmp(*(char **)d1, *(char **)d2));
}
