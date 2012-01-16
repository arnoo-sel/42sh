/*
** tools.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Wed May  7 00:44:07 2008 arnaud sellier
** Last update Wed May  7 00:44:57 2008 arnaud sellier
*/

#include "42sh.h"

int	n_is_char_in_str(char c, char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (c == str[i])
	return (1);
      i++;
    }
  return (0);
}
