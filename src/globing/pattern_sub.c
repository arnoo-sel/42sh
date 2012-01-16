/*
** pattern_sub.c for 42sh in /home/jartho_d/42sh/mysh
** 
** Made by adrien1 jarthon
** Login   <jartho_d@epitech.net>
** 
** Started on  Fri May 23 17:05:57 2008 adrien1 jarthon
** Last update Thu Jun  5 11:10:59 2008 adrien1 jarthon
*/

#include "42sh.h"

int		pre_pattern_dump(char **str, char **name,
				  char **inhib, t_vector **stack)
{
  int		begin;

  *name = xsmalloc(my_strlen(str[0]));
  *inhib = xsmalloc(my_strlen(str[0]));
  *stack = vector_init();
  begin = 0;
  while (str[0][begin] && (str[0][begin] != OPEN_BRACE))
    {
      (*name)[begin] = globbed_to_std(str[0][begin]);
      (*inhib)[begin] = str[1][begin];
      begin++;
    }
  return (begin);
}

void		post_pattern_dump(char **str, char *name, char *inhib, int end)
{
  int		pos;

  pos = -1;
  while (str[0][end + (++pos) + 1])
    name[pos] = globbed_to_std(str[0][end + pos + 1]);
  name[pos] = 0;
  my_strcpy(inhib, str[1] + end + 1);
}

t_vector	*find_all_pattern(char **str)
{
  t_vector	*stack;
  char		*name;
  char		*inhib;
  int		begin;
  int		end;
  int		k;
  int		l;

  end = (k = begin = pre_pattern_dump(str, &name, &inhib, &stack)) - 1;
  while (str[0][++end] && (str[0][end] != CLOSE_BRACE));
  if (!str[0][end])
    return (stack);
  while (++k < end)
    {
      l = begin;
      while (((str[0][k] != ',') || str[1][k]) && (k < end))
	{
	  name[l] = str[0][k];
	  inhib[l++] = str[1][k++];
	}
      post_pattern_dump(str, name + l, inhib + l, end);
      vector_push(stack, my_strdup(name));
    }
  msfree(name, inhib, 0);
  return (stack);
}

