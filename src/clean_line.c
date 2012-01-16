/*
** clean_line.c for 42sh in /u/epitech_2012/sellie_a/cu/42sh/mysh
** 
** Made by arnaud sellier
** Login   <sellie_a@epitech.net>
** 
** Started on  Thu May  8 18:14:25 2008 arnaud sellier
** Last update Thu Jun  5 11:11:30 2008 arnaud sellier
*/

#include "42sh.h"

void	clean_line(char buf[BUF], char out[BUF])
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  while (buf[i] == ' ')
    i++;
  my_memset(out, 0, BUF);
  while (buf[i])
    {
      out[j] = buf[i];
      j++;
      i++;
      if ((buf[i] == ' ') && (buf[i + 1] != 0))
	{
	  out[j] = buf[i];
	  j++;
	  i++;
	}
      while (buf[i] == ' ')
	i++;
    }
  out[i] = 0;
}
